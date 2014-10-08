#include "user.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	// TEST FILE FOR USER CLASS
	string temp = "sasha";
	User* test = new User(temp);
	cout << "name: " << test->getName() << endl;
	//test->incrementPage("google.com");
	//cout << endl;
	test->addPage("idk");
	test->addCompany("apple");
	test->incrementPage("idk");
	cout << "companies" << endl;
	set<string> testComp = test->getCompanies();
	cout << "num companies: " << testComp.size() << endl;
	for(typename set<string>::iterator it = testComp.begin(); it != testComp.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << endl;
	cout << "history" << endl;
	map<string, int> testHistory = test->getHistory();
	for(map<string, int>::iterator it = testHistory.begin(); it != testHistory.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}
	cout << endl;
	cout << "most visited" << endl;
	vector<string> most = test->getMostVisited();
	for(vector<string>::iterator it = most.begin(); it != most.end(); ++it)
	{
		cout << *it << endl;
	}
	delete test;
	return 0;
}