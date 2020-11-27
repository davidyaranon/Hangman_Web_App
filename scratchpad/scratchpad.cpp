#include <iostream>
#include <string>

using namespace std;

int main(){

	std::string my_str = "TEST WORD";
	std::cout << my_str.size() << endl;
	my_str.erase(my_str.begin()+ 1);
	std::cout << my_str << std::endl;
	std::cout << my_str.size() << endl;

	return 0;
}
