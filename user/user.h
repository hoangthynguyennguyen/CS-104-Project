#ifndef USER_H_
#define USER_H_
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

class User
{
public:
	User(); //should never get called
	User(std::string username);
	~User(); //writes back to file when done

	//returns the user's name
	const std::string getName() const;
	//adds a new page to the history map with 0 times visited
	void addPage(const std::string newPage);
	//increments the number of times visited for a webpage
	void incrementPage(const std::string thePage);
	//adds a company to the set of ads
	void addCompany(std::string newCompany);
	//returns a map with the webpages and number of times visited
	const std::map<std::string, int>& getHistory() const;
	//returns a set with the ad companies
	const std::set<std::string>& getCompanies() const;
	//returns a vector with the webpages in order of most visited to least visited
	const std::vector<std::string>& getMostVisited(); 

private:
	std::string name;
	std::map<std::string, int>* history; //holds the webpages and number of times visited
	std::set<std::string>* companies; //holds the ad companies
	std::vector<std::string>* mostVisited;
	bool userExists;
};

#endif