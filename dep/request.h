#ifndef UCMREQUEST
#define UCMREQUEST

#include <string>
#include <curl/curl.h>

#include <server.h>
#include <thread>

// #define DEBUG

enum Method {GET, POST};
enum TypeRequest{BLOCKING, ASYNC};

class Request;


class Request{
	ucm::json data;
	Method method;
	std::string response;
	std::string url;
	std::function<void (std::string)> callback;

	CURL* curl;
	curl_slist *chunk;

	static int counter;

	std::thread t;

	static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) { 
		//callback must have this declaration
		//buf is a pointer to the data that curl has for us
		//size*nmemb is the size of the buffer

		Request* req = (Request*)up;
		

		for (int c = 0; c<size*nmemb; c++){
			req->response.push_back(buf[c]);
		}

		// std::cout << req->response << std::endl;
		// req->callback(responseText);
		return size*nmemb; //tell curl how many bytes we handled
	}

	static void threadExecute(Request* r){
		#ifdef DEBUG
		std::cout << "Initiating CURL Request" << std::endl;
		#endif
		//r->perform();
		curl_easy_perform(r->curl);
		#ifdef DEBUG
		std::cout << "Response received, calling callback" << std::endl;
		#endif
		r->callback(r->response);
	}

	std::string url_encode(const std::string &value) {
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << std::hex;

		for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
			std::string::value_type c = (*i);

			// Keep alphanumeric and other accepted characters intact
			if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
				escaped << c;
				continue;
			}

			// Any other characters are percent-encoded
			escaped << std::uppercase;
			escaped << '%' << std::setw(2) << int((unsigned char) c);
			escaped << std::nouppercase;
		}

		return escaped.str();
	}

	Request(){}

public:

	Request(Method method, std::string url, ucm::json data, std::function<void (std::string)> cb){
		if (counter == 0){
			curl_global_init(CURL_GLOBAL_ALL);
		}
		counter++;

		this->method = method;
		this->url = url;
		this->data = data;
		callback = cb;

		curl = curl_easy_init();
		chunk = NULL;

		
		const char* c_url = this->url.c_str();

		if (this->method == GET){
			std::string tempURL = this->url;
			
			if (this->data.size() > 0){
				tempURL += '?';
				for (auto item : this->data.items()){
					std::string key = url_encode(item.key());
					std::string value = url_encode(item.value());

					tempURL += key;
					tempURL += '=';
					tempURL += value;
				}
			}
			
			c_url = tempURL.c_str();

			
		}
		else if (method == POST){
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}");
			if (this->data.size() > 0){
				std::string json = this->data.dump();
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)json.size());
				curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, json.c_str());
			}
		}

		curl_easy_setopt(curl, CURLOPT_URL, c_url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		
	}

	void send(TypeRequest type=ASYNC){
		if(type == ASYNC){
			t = std::thread(threadExecute, this);
		}
		else if (type == BLOCKING){
			curl_easy_perform(curl);
			callback(response);
		}
	}

	void addHeader(std::string header){
		chunk = curl_slist_append(chunk, header.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	}

	~Request(){
		#ifdef DEBUG
		std::cout << "Time to clean up..." << std::endl;
		#endif
		if (t.joinable()){
			#ifdef DEBUG
			std::cout << "Oops, we are still executing, so wait" << std::endl;
			#endif
			t.join();
			
		}
		else{
			#ifdef DEBUG
			std::cout << "We are not executing, go ahead." << std::endl;
			#endif
		}
		#ifdef DEBUG
		std::cout << "Cleaning up now..." << std::endl;
		#endif
		curl_easy_cleanup(curl);
		counter--;
		if (counter == 0){
			curl_global_cleanup();
		}
	}

};

int Request::counter = 0;

#endif
