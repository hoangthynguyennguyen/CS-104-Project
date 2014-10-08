#include "user.h"
#include <fstream>

using namespace std;

User::User()
{
	history = new map<string, int>;
	companies = new set<string>;
	mostVisited = new vector<string>;
	name = "";
}

User::User(string username) : name(username)
{
	history = new map<string, int>;
	companies = new set<string>;
	mostVisited = new vector<string>;

	string tempName = "user/users/" + name + ".txt";
	
	
	//check if the user already has a file
	userExists = ifstream(tempName.c_str()); 
	
	if(userExists)
	{
		string temp = "";
		ifstream file(tempName.c_str());
		if(file.fail())
		{
			cout << "failed to open" << endl;
		}
		//get the first line which has number of webpages
		getline(file, temp);
		stringstream ss;
		ss << temp;
		int numPages;
		ss >> numPages;
		//populate the history map
		for(int i = 0; i < numPages; i++)
		{
			getline(file, temp);
			string tempPage = temp.substr(0, temp.find(" "));
			string num = temp.substr(temp.find(" ") + 1);
			stringstream ss1;
			ss1 << num;
			int tempNum;
			ss1 >> tempNum;
			history->insert(make_pair(tempPage, tempNum));
		}
		//get the number of ad companies
		int numCompanies;
		getline(file, temp);
		stringstream ss2;
		ss2 << temp;
		ss2 >> numCompanies;
		//populate the set of companies
		for(int i = 0; i < numCompanies; i++)
		{
			getline(file, temp);
			companies->insert(temp);
		}
	}
	else{
		ofstream ofile(tempName.c_str());
	}
}

User::~User()
{
	string tempName = "user/users/" + name + ".txt";
	ofstream file(tempName.c_str());
	int numPages = history->size();
	int numCompanies = companies->size();
	file << numPages << endl;
	for(map<string, int>::iterator it = history->begin(); it != history->end(); ++it)
	{
		file << it->first << " " << it->second << endl;
	}
	file << numCompanies << endl;
	for(typename set<string>::iterator it = companies->begin(); it != companies->end(); ++it)
	{
		file << *it << endl;
	}

	delete history;
	delete companies;
	delete mostVisited;
}

const string User::getName() const
{
	return name;
}

void User::addPage(const string newPage)
{
	//if the page doesn't exist yet, add it
	if(history->find(newPage) == history->end())
	{
		history->insert(make_pair(newPage, 0));
	}
	else
	{
		incrementPage(newPage);
	}
}

void User::incrementPage(const string thePage)
{
	map<string, int>::iterator it = history->find(thePage);
	if(it != history->end())
	{
		++(it->second);
	}
}

void User::addCompany(const string newCompany)
{
	companies->insert(newCompany);
}

const map<string, int>& User::getHistory() const
{
	return *history;
}

const set<string>& User::getCompanies() const
{
	return *companies;
}

const vector<string>& User::getMostVisited()
{
	//Trying to solve the duplicate problem? 
	while (!mostVisited -> empty()){
		mostVisited -> pop_back();
	}
	map<int, string> visited; //initial map
	map<string, int> collisions; //used for multiple pages with the same number of times visited

	for(map<string, int>::iterator it = history->begin(); it != history->end(); ++it) //go through the history
	{
		map<int, string>::iterator it2 = visited.find(it->second); //check if the number of pages already exists in visited
		if(it2 == visited.end()) //if it doesn't put into visited
		{
			visited.insert(make_pair((it->second), (it->first)));
		}
		else //if it does put into collisions
		{
			collisions.insert(make_pair((it->first), (it->second)));
		}
	}
	if(collisions.empty()) //nothing to fix
	{
		for(map<int, string>::reverse_iterator rit = visited.rbegin(); rit != visited.rend(); ++rit)
		{
			mostVisited->push_back(rit->second);
		}
	}
	else
	{
		for(map<int, string>::reverse_iterator rit = visited.rbegin(); rit != visited.rend(); ++rit)
		{
			mostVisited->push_back(rit->second); //put in whatever is in visited first, then check for collisions
			for(map<string, int>::iterator it3 = collisions.begin(); it3 != collisions.end(); ++it3)
			{
				if(it3->second == rit->first)
				{
					mostVisited->push_back(it3->first);
					collisions.erase(it3->first);
				}
			}
		}
	}
	return *mostVisited;
}