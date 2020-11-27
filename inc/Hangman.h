#include <server.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>

//GLOBAL VARIABLES...
int randfile;
std::string category;
crowJSON::json hangmanState;
crowJSON::json wordJSON;
std::vector<std::string> drawings = {"0_Hangman.png", "1_Hangman.png", "2_Hangman.png", "3_Hangman.png", "4_Hangman.png", "5_Hangman.png", "6_Hangman.png"};
std::string word = "";
std::vector<int> locationsGuessedCorrectly;
std::vector<std::string> lettersGuessedIncorrectly;
int size = 0;

//READING THESE FILES IN THIS WAY CAUSES THE WORD TO RETURN WITH THE \r AT THE END OF THE STRING!
std::vector<std::string> readWordsFile(std::string fileName){
    std::ifstream file(fileName);
    std::string temp;
    std::vector<std::string> words;
    while(std::getline(file, temp)){
        words.push_back(temp);
    }
    return words;
}

std::string fileParse(std::string fileName){
	std::vector<std::string> listOfWords = readWordsFile(fileName);
    int index = rand() % listOfWords.size();
    std::string word1 = listOfWords[index];
    return word1;
}

void generateWord(){
   	randfile = rand() % 3;
    if(randfile == 1){
		category = "Animals";
        word = fileParse("textFiles/Animals.txt");
    }
    else if(randfile == 2){
		category = "Kitchen";
    	word = fileParse("textFiles/Foods.txt");
    }
    else{
		category = "Random Objects";
        word = fileParse("textFiles/RandomObjects.txt");
    }
	std::transform(word.begin(), word.end(), word.begin(), ::toupper);
}

void init(){ //Initialization of everything needed for game
	srand(time(NULL));
	hangmanState["all"] = drawings;
	generateWord(); //Word is now chosen from list of words
	wordJSON["length"] = word.size() - 1;
	wordJSON["fullWord"] = word;
	wordJSON["category"] = category;
	lettersGuessedIncorrectly.clear();
	locationsGuessedCorrectly.clear();
}


crowJSON::json checkLetter(std::string letter){
	crowJSON::json check;
	check["hasLetter"] = false;
	check["location"] = NULL;
	for(int i = 0; i < word.size(); i++){
		std::string s{word[i]};
		if(letter == s){
			check["hasLetter"] = true;
			word[i] = ' ';
			locationsGuessedCorrectly.push_back(i);
		}
	}
	if(check["hasLetter"] == false){
		lettersGuessedIncorrectly.push_back(letter);
	}
	check["lettersGuessed"] = lettersGuessedIncorrectly;
	check["location"] = locationsGuessedCorrectly;
	return check;
}

crowJSON::json getInit(){
	return hangmanState;
}

crowJSON::json getWord(){
	return wordJSON;
}
