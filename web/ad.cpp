#include "ad.h"

using namespace std; 

Ad::Ad(){

}//default constructor 
Ad::Ad(string filename, double bid, string keyWord){
	_name = filename; 
	_bid = bid;
	_keyWord = keyWord;
}
Ad::~Ad(){

}
string Ad::filename(){
	return _name; 
}
string Ad::getKey(){
	return _keyWord;
}
double Ad::getScore(){
	return _bid;
}
void Ad::addScore(double add){
	_bid += add; 
}
void Ad::setName(string name){
	string cleanName;
	int findLetter = 0;
	while(name[findLetter] == char(32)){
		findLetter++; 
	}
	cleanName = name.substr(findLetter);
	stringstream ss(cleanName); 
	string finalName = "";
	while (ss >> cleanName){
		finalName += cleanName; 
		finalName += " ";
	}
	if(finalName[finalName.size() - 1] == char(32)){
		finalName.pop_back();
	}
	_name = finalName;
}
void Ad::setScore(double bidVal){
	_bid = bidVal;
}
void Ad::setKeyWord(string keyWord){
	_keyWord = keyWord;
}