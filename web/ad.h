#ifndef AD_H
#define AD_H

#include <iostream> 
#include <string> 
#include <stdlib.h>
#include <sstream>

using namespace std; 

class Ad{ 
public: 
	Ad(); 
	Ad(std::string filename, double bid, std::string keyWord);
	~Ad(); 
	string filename(); 
	double getScore(); 
	string getKey();
	void addScore(double add);
	void setName(string name);
	//void setScore(string bid);
	void setScore(double bid);
	void setKeyWord(string keyWord);
private: 
	std::string _name; 
	double _bid; 
	std::string _keyWord; 
};

#endif