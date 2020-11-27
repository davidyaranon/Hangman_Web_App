#include <server.h>
#include <Hangman.h>

using namespace crowJSON;


int main(int argc, char** argv){

    init(); //Initializes all variables needed for hangman
    Server server(argc, argv);
    server.renderHTML("/", "index.html");


    
    server.route("/initial", [&](const request& req, response& res){
        init();
        res.sendJSON(getInit());
    });



    server.route("/startGame", [](const request& req, response& res){
        json theWord = getWord();
        res.sendJSON(theWord);
    });



    server.route("/checkLetter", [&](const request& req, response& res){
        if(req.url_params.hasKey("theLetter")){
            std::string letter = req.url_params.get("theLetter");
            json check = checkLetter(letter);
            res.sendJSON(check);
        }
        else{
            res.sendError400();
        }
    });



    server.route("/getDrawings", [](const request& req, response& res){
        res.sendJSON(getInit());
    });



    server.run();
}
