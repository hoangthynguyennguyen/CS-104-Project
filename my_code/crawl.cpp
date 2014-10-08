#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void crawl(string, string, vector<string>&); 
//int main(string seed_file, string output){
bool checkFile(string&, string& output);
int main(int argc, char* argv[]){
	string seed_file = argv[1];
	string output = argv[2];
	bool alreadyThere; 
	ifstream myFile(seed_file.c_str());
	vector<string> pageNames;
	if (myFile.fail()){
		cout << "You've failed to read in a filename: " << seed_file << endl;
	}
	else{
		string tempPage;
		while(myFile.good()){
			myFile >> tempPage;
			bool runCrawl = true;
			for (int i = 0; i < pageNames.size(); i++){
				if(tempPage == pageNames[i]){
					runCrawl = false;
				}
			}
			if (runCrawl != false){
				crawl(tempPage, output, pageNames);
			}
			tempPage.clear();
		}
	}

	ofstream oFile(output.c_str());
	

	//Need to work front -> back because the first item will be put at the bottom and you
	//want it in the order it was found
	for(int i = 0 ; i < pageNames.size() ; i++){
		oFile << pageNames[i] << endl;
	}
	oFile.close();
	return 0;
}

void crawl(string seed_file, string output, vector<string> &pageNames) 
{
	if(seed_file.size() == 0){
		//cout << "There's no file here, just white space" << endl;
		return;
	}
	if(seed_file.size() != 0){
		pageNames.push_back(seed_file);
	}
	ifstream currPage(seed_file.c_str()); 
	string temp;
	string every = "";
	while(currPage.good()){
		currPage >> temp;
		every += temp;
	}
	//cout << "Testing to see if every worked " << every << endl;
	string linkName = "";
	for(int i = 0; i < every.size(); i++){
		if(every[i] == '['){
			int j = i;
			while(every[j] != ']'){
				j++;
			}
			j = j + 1; //incrementing to the first open paren
			linkName = "";
			j = j + 1; //now I'm ignoring that first paren
			while(every[j] != ')'){
				if (every[j] != 34){
					linkName.push_back(every[j]);
				}
				j++;
			}
			//cout << "This is the name of my link" << linkName << endl;
			bool alreadyStarted = false;
			for (int k = 0; k < pageNames.size(); k++){
				if(pageNames[k] == linkName){
					alreadyStarted = true;
				}
			}
			if (checkFile(linkName, output) != true && alreadyStarted != true){
				crawl(linkName, output, pageNames);
			}
			
		}
	}

}
bool checkFile(string &checkFile, string& output){
	//ifstream _checkFile(checkFile);
	ifstream _checkFile(output.c_str());
	string temporary = "";
	while(_checkFile.good()){
		_checkFile >> temporary;
		if(temporary == checkFile){
			return true;
		}
		temporary.clear();
	}
	return false;
}