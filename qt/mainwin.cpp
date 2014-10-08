#include "mainwin.h"
#include "../lib/mergesort2.h"
#include <sstream>
#include <string>
#include <exception>
#include <list>
#include <QApplication> 
#include <iostream>
#include <QFont>




using namespace std;

MainWin::MainWin(std::string input, std::string adfile, std::string billfile, std::string username, QWidget *parent) : QMainWindow(parent){
	setWindowTitle(QString::fromStdString("O(Infinity)"));
	indexName = input;
	outFileName = billfile;
	_userName = username;
	currentUser = new User(_userName);
	temp= new Profile(currentUser);
	proList.push_back(temp);
	bool success = openIndex(input); //Make sure you can open your file
	bool readAdsIn = readAds(adfile); 
	if(!readAdsIn){
		cout << "Error, failed to read in properly" << endl;
	}
	if(!success){
		cout << "Error, failed to read in properly" << endl;
	}
	else{
		//Changing fonts because why not
		QFont newFont("Courier", 12, QFont::Bold, true);
		//set font of application
		QApplication::setFont(newFont);
		
		//Allocate memory for all widgets 
		windowOpen = false;
		adOpen = false;
		profileOpen = false;
		fileName = new QLabel(QString::fromStdString("Single Word: Enter one word. \nAnd/Or: Enter words separated by commas, end the final word with a period, then select button \nSelect the button according to how you want your results sorted")); 
		ads = new QLabel(QString::fromStdString("Ads: " ));
		btnQuit = new QPushButton("&Quit"); 
		btnSearch = new QPushButton("&Single Word: Alphabetical");
		btnSearchPage = new QPushButton("&Single Word: PageValue");
		btnAnd = new QPushButton("&And: Alphabetical");
		btnOr = new QPushButton("&Or: Alphabetical");
		btnAndPage = new QPushButton("&And: PageValue");
		btnOrPage = new QPushButton("&Or: PageValue");
		btnViewPro = new QPushButton("&View Profile");
		searchInput = new QLineEdit("Please enter a search");
		resultsList = new QListWidget;
		adsList = new QListWidget;
		winLayout = new QVBoxLayout; 
		buttLayout = new QHBoxLayout;
		buttLayout2 = new QHBoxLayout;

		//Set up the layout
		centerWidget = new QWidget(this);
		centerWidget -> setLayout(winLayout);
		this -> setCentralWidget(centerWidget); //because I wanna be the CENTER OKAY

		//add all widget to layout
		winLayout -> addWidget(fileName, 0);
		winLayout -> addWidget(searchInput, 0);
		winLayout -> addWidget(btnViewPro, 0);
		buttLayout -> addWidget(btnSearch, 0);
		buttLayout -> addWidget(btnAnd, 0);
		buttLayout -> addWidget(btnOr, 0);
		buttLayout2 -> addWidget(btnSearchPage, 0);
		buttLayout2 -> addWidget(btnAndPage, 0);
		buttLayout2 -> addWidget(btnOrPage, 0);
		winLayout -> addLayout(buttLayout, 2);
		winLayout -> addLayout(buttLayout2, 2);
		winLayout -> addWidget(resultsList, 0);
		winLayout -> addWidget(ads, 0 );
		winLayout -> addWidget(adsList, 0);
		winLayout -> addWidget(btnQuit, 0);
		

		//connect clicked signal of the buttons to the right slot 
		connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit())); //WOOHOO! Works!

		//Alphabetical Order buttons
		connect(btnSearch, SIGNAL(clicked()), this, SLOT(runSearchAlpha()));
		connect(btnAnd, SIGNAL(clicked()), this, SLOT(runAndAlpha()));
		connect(btnOr, SIGNAL(clicked()), this, SLOT(runOrAlpha()));
		//PageValue buttons
		connect(btnSearchPage, SIGNAL(clicked()), this, SLOT(runSearchPage()));
		connect(btnAndPage, SIGNAL(clicked()), this, SLOT(runAndPage()));
		connect(btnOrPage, SIGNAL(clicked()), this, SLOT(runOrPage()));
		connect(resultsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNewWin()));
		connect(adsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openPopUp()));
		connect(btnViewPro, SIGNAL(clicked()), this, SLOT(openProfile()));
		connect(temp, SIGNAL(closeProfile()), this, SLOT(needToClose()));
	}//end else of if the file opened successfully

} //end constructor

MainWin::~MainWin(){
	//Deleting dynamically allocated non-qt 
	ofstream outFile(outFileName);
	
	for(std::map<string,double>::iterator it = billTotal.begin(); it != billTotal.end(); ++it){
		outFile << it -> first; 

		outFile << endl; 
		outFile << it -> second; 
		outFile << endl; 
		outFile << endl;
	}
	outFile.close();
	while(pageNames.empty() != true){
		delete pageNames.back();
		pageNames.pop_back();
	}
	while(pointerList.empty() != true){
		delete pointerList.back();
		pointerList.pop_back();
	}
	delete currentUser;

}

void MainWin::needToClose()
{
	profileOpen = false; //
}

void MainWin::displayResults(vector<WebPage*> cross){
	resultsList -> clear();
	string name = "";
	for (int i = cross.size() -1 ; i >= 0; i--){
		name = cross[i] -> filename();
		QListWidgetItem* temp = new QListWidgetItem(QString::fromStdString(name)); //this needs to be delete somewhere
		resultList.push_back(temp);
		resultsList -> insertItem(0, temp);
		name = "";
	}
	//Random test
	
}

void MainWin::openNewWin(){
	string webTemp = resultsList -> currentItem() -> text().toStdString();
	WebPage* tempWeb = NULL;
	for(unsigned int i = 0; i < pageNames.size(); i++){
		if(pageNames[i] -> filename() == webTemp){
			//cout << webTemp << "'s name is a match" << endl;
			tempWeb = pageNames[i];
		}
	}
	currentUser -> addPage(tempWeb -> filename());
	temp -> addHistory(tempWeb -> filename());
	//If it hasn't been opened yet
	if(windowOpen == false){
		SearchWin* temp = new SearchWin(tempWeb, pageNames, this);
		lookUpList.push_back(temp);

		temp -> show();
		windowOpen = true;
	}
	else{
		//Refreshing the page in the case you accidentally close
		if(lookUpList.front() -> isVisible() == false){
			SearchWin* temp = new SearchWin(tempWeb, pageNames, this);
			lookUpList.push_back(temp);

			temp -> show();
			windowOpen = true;
			lookUpList.pop_front(); //delete the one in the front now? 
		}
		else{ //Else just call the searchwin's refresh function
			lookUpList.front() -> refreshPage(tempWeb);
		}
	}
	//Refresh profile
	if(profileOpen == true){
		openProfile();
	}
} //Open the results window for AND/OR/Single

//Open popup window for adds 
void MainWin::openPopUp(){
	string adTemp = adsList -> currentItem() -> text().toStdString();
	
	Ad* tempAd = NULL; 

	for(unsigned int i = 0; i < adNames.size(); i++){
		if(adNames[i] -> filename() == adTemp){
			//cout << "I found a match" << endl;
			tempAd = adNames[i];
			currentUser -> addCompany(tempAd -> filename());
			break;
		}
	}
	if(adOpen == false){
		Popup* temp = new Popup(tempAd, this);
		adList.push_back(temp);


		temp -> show();
		double originalBill = billTotal.find(tempAd -> filename()) -> second;
		double addToBill = tempAd -> getScore();
		double newTotal = originalBill + addToBill; 
		billTotal.find(tempAd -> filename()) -> second = newTotal;
		adOpen = true;
	}
	else{
		if(adList.front() -> isVisible() == false){
			Popup* temp = new Popup(tempAd, this);
			adList.push_back(temp);

			temp -> show();
			double originalBill = billTotal.find(tempAd -> filename()) -> second;
			double addToBill = tempAd -> getScore();
			double newTotal = originalBill + addToBill; 
			billTotal.find(tempAd -> filename()) -> second = newTotal;
			adOpen = true;
			adList.pop_front();
		}
		else{
			adList.front() -> refreshPop(tempAd);
			double originalBill = billTotal.find(tempAd -> filename()) -> second;
			double addToBill = tempAd -> getScore();
			double newTotal = originalBill + addToBill; 
			billTotal.find(tempAd -> filename()) -> second = newTotal;
		}
	}
	if(profileOpen == true){
		openProfile();
	}
}
void MainWin::openProfile(){
	if (profileOpen != true){
		temp -> refreshPage(_userName);
		temp -> show();
		profileOpen = true;
	}
	else{
		temp -> refreshPage(_userName);
		temp -> show();
	}
}
//Version that takes in specfic search 
void MainWin::runPageVal(vector<WebPage*>& pageName){
	Set<WebPage*> results; Set<WebPage*> originalResults;
	for (unsigned int i = 0; i < pageName.size(); i++){
		results.insert(pageName[i]);
		originalResults.insert(pageName[i]);
	}

	//Set with the results of the word search 
	for (vector<WebPage*>::iterator vecIt = pageName.begin(); vecIt != pageName.end(); ++vecIt){
		WebPage* temp = *vecIt;
		results = results.setUnion(originalResults);
		results = results.setUnion(temp -> allOutgoingLinks());
		results = results.setUnion(temp -> allIncomingLinks());
	}

	pageName.clear();

	for (Set<WebPage*>::iterator copy = results.begin(); copy != results.end(); ++copy){
		WebPage* temp = *copy;
		pageName.push_back(temp);
	}

	vector < vector <WebPage*> > scoreIt; 
	for(unsigned int i = 0; i < pageName.size(); i++){ //going through all pages
		vector <WebPage*> outgoing;
		Set <WebPage*> tempSet = pageName[i] -> allOutgoingLinks();
		for(Set<WebPage*>::iterator out = tempSet.begin(); out != tempSet.end(); ++out){
			WebPage* temporary = *out;
			for(unsigned int j = 0; j < pageName.size(); j++){
				if(temporary -> filename() == pageName[j] -> filename()){
					outgoing.push_back(temporary);
				}
			}
		}
		scoreIt.push_back(outgoing);
	}
	
	double initialVal = 1.0 / pageName.size();
	for (unsigned int i = 0; i < pageName.size(); i++){
		pageName[i] -> setPageValue(initialVal);
	}

	//And now we begin the probability calculations!
	for (int k = 0; k < 30; k++){
		double bank = 0; 
		for (unsigned int i = 0; i < scoreIt.size(); i++){ 
			double addProb = 0;
			if(scoreIt[i].size() == 0){
				addProb = (pageName[i] -> _pageValue()) / scoreIt.size();
				for (unsigned int j = 0; j < scoreIt.size(); j++){
					pageName[j] -> updateVal(addProb);
				}
			}
			else{
				addProb = ((.85) * (pageName[i] -> _pageValue())) / scoreIt[i].size();
				for (unsigned int j = 0; j < scoreIt[i].size(); j++){
					scoreIt[i][j] -> updateVal(addProb);
				}
				bank += ((.15)*(pageName[i] -> _pageValue())) / scoreIt.size();
			}
		}
		for(unsigned int i = 0; i < scoreIt.size(); i++){
			double addProb = pageName[i] -> returnUpdate(); 
			addProb += bank;
			pageName[i] -> setPageValue(addProb);
			pageName[i] -> updateVal(0 - (pageName[i] -> returnUpdate()));
		}


		double total = 0.0;
		for(unsigned int i = 0; i < scoreIt.size(); i++){
			total += pageName[i] -> _pageValue();
		}
	}

} //Organizes based off pageRank value


bool MainWin::openIndex(std::string initialFile){ //Used to open the search engine via the file passed in by command
	ifstream myFile(initialFile.c_str());
	if(myFile.fail()){
		cout << "You've failed to read in a filename:" << initialFile << endl;
	}
	else{
		vector<WebPage*> pageNames;
		//Getting the files 
		bool success = getFiles(myFile, pageNames);
		if(success != true){
			cout << "Failed to get files" << endl;
			return false;
		}
	} 
	return true; //for now
}

bool MainWin::getFiles(std::ifstream &myFile, std::vector<WebPage*> &pages){
	string webName;
	bool alreadyThere; //to see if the files already there 
	while(!myFile.fail()){
		webName.clear();
		alreadyThere = false;
		myFile >> webName; 
		if(webName.size()== 0){ //ignoring the new line so that I don't try to open its webpage
			webName.clear();
			break;
		}
		if (pages.size() != 0){ //Checking to see if the webpage has already been opened
			for(unsigned int i = 0; i < pages.size(); i++){
				if(pages[i] -> filename() == webName){
					cout << webName << " has already been opened" << endl;
					alreadyThere = true;
				}
			}
		}
		if (myFile.fail()){
			if(webName.size() != 0){
				cout << "You have failed to read in the name: " << webName << endl;
				return false;
			}
		} 
		if(webName.size()!= 0 && alreadyThere == false){ //if it's not the new line character or not already there
			WebPage* temp = new WebPage(webName);
			pages.push_back(temp); //
			pageNames.push_back(temp); //this is the private variable
		}
		else{
			cout << "You've hit the end of the file" << endl;
			continue;
		}
	}

	if (myFile.fail()){
		if (webName.size() != 0){
			cout << "Failed to open file: " << webName << endl;
			return false;
		}
	}
	//Grab and add the links to the webpages I just made 
	for(unsigned int i = 0; i < pages.size(); i++){
		if(pages[i] -> hasLink() == true){
			getLinks(pages[i], pages);
		}
	}
	return true;
} //end get files

void MainWin::getLinks(WebPage* currPage, std::vector<WebPage*>& pages){
	//go through the list of name strings of the links to add the links
	vector<string> linkNames = currPage -> _linkNames();
	for (unsigned int k = 0; k < linkNames.size(); k++){
		for (unsigned int j = 0; j < pages.size(); j++){
			if(pages[j] -> filename() == linkNames[k]){
				currPage -> parse(pages[j]);
			} //end if file name equals 
		} //end for pages
	} //end for link names

}
void MainWin::setIndexes(){
	for (unsigned int i = 0; i < pageNames.size(); i++){
		pageNames[i] -> setIndex(i);
	}
}
void MainWin::lowerCase(std::string& input){
	for (unsigned int i = 0; i < input.size(); i++){
		if (input[i] >= 'A' && input[i] <= 'Z'){
			input[i] = input[i] + 32; 
		}
	}
}
bool MainWin::cleanUp(std::string& input, int& wordCount, std::vector<string>& search){
	//cout << "this is the input " << input << endl;
	bool endFound = false;
	string word = "";	
	for (unsigned int i = 0; i <= input.size(); i++){
		if(input[i] != ',' && input[i] != '.'){ //Checking to see that it's not word separation
			if(input[i] == ' '){

			}
			if(input[i] >= 'a' && input[i] <= 'z'){ //add lowercase because I treat things as lower case behind the scenes
				word.push_back(input[i]);
			}
			if(input[i] >= 'A' && input[i] <= 'Z'){ //Convert upper case to lower case
				//cout << "This is input" << input[i] << endl;
				input[i] = input[i] + 32;
				word.push_back(input[i]);
			}
			if(input[i] >= '0' && input[i] <= '9'){ //Treat numbers as letters
				word.push_back(input[i]);
			}
			else{ //If it's any other kind of character, ignore it

			}
		}
		if(input[i] == ',' || input[i] == '.'){ //Things that would separate words or indicate end of string
			search.push_back(word);
			wordCount++;
			word = "";
			if(input[i] == '.'){ //this is the end 
				endFound = true;
				return endFound; //terminate right away to ignore anything that comes after
			}
		}
	}
	return endFound;
	
}

void MainWin::runSearchAlpha(){
	//Enter code for single word here
	string input = searchInput -> text().toStdString();
	lowerCase(input);

	//easter eggs!
	if(input == "pink"){
		setStyleSheet("background-color: pink;");
	}
	if (input == "blue"){
		setStyleSheet("background-color: blue;");
	}
	//testing for ad results
	displayAds(input);
	Set<WebPage*> match;
	vector<WebPage*> mylist;

	bool matches = false;
	for(unsigned int i = 0; i < pageNames.size(); i++){
		if(pageNames[i] -> allWords().contains(input) == true){
			match.insert(pageNames[i]);
			matches = true;
		}
	}//end for pageNames
	//If it's not there
	
	if (matches == false){
		cout << "This search does not yield results" << endl;
	}//end matches = false

	for (Set<WebPage*>::iterator it=match.begin(); it!=match.end(); ++it){ //copy the set into a vector
		WebPage* addIt = *it;
		mylist.push_back(addIt);
	}
	expandAlpha(mylist);

	mergeSort<WebPage*, AlphaStrComp<WebPage*> > obj;
	AlphaStrComp <WebPage*>  comp1; 
	
	obj.merge_sort(mylist, comp1); //alphabetically sort it 
	
	if(mylist.size() > 0){
		displayResults(mylist);
	}
	else{
		cout << "No results found" << endl; //This is redundant to the other if...
		resultsList -> clear();
	}

}


void MainWin::runAndAlpha(){
	string input = searchInput -> text().toStdString();
	
	vector<string> search;
	vector<WebPage*> andAlpha; 
	int wordCount = 0; 

	//Cleans up the user input
	bool clean = cleanUp(input, wordCount, search);
	displayAdsOr(search);
	if (clean == false){
		resultsList -> clear();
		cout << "Please follow the format of comma separation and period termination: " << endl; 
		cout << "Example: Word, word, lastword." << endl;
	}
	else{
		if(wordCount < 2){
			cout << "You didn't enter enough words" << endl;
			resultsList -> clear();
		}
		else{
			map<string, Set<WebPage*>*> intersects;
			for (unsigned int i =0; i < search.size(); i++){
				Set <WebPage*>* match = new Set<WebPage*>;
				pointerList.push_back(match);
				string temp = search[i]; 
				//If the words in there, throw page into my set! 
				
				
				for (unsigned int j =0; j < pageNames.size(); j++){
					if(pageNames[j] -> allWords().contains(temp) == true){
						match -> insert(pageNames[j]);
					}
				}
				//Now add that set into my map with the word
				intersects.insert(pair<string, Set<WebPage*>*>(search[i], match));
			}

			Set<WebPage*> cross = (*intersects.at(search[0]));

			for (unsigned int i = 1; i < search.size(); i++){
				cross = cross.setIntersection(*intersects.at(search[i]));
			}

			expandSet(cross, andAlpha);
			//Looking one level in 
			expandAlpha(andAlpha);
		

			mergeSort<WebPage*, AlphaStrComp<WebPage*> > obj;
			AlphaStrComp <WebPage*>  comp1; 
			obj.merge_sort(andAlpha, comp1); //alphabetically sort it 

			if (andAlpha.size() > 0){
				displayResults(andAlpha);
			}
			else{
				cout << "No results found" << endl;
				resultsList -> clear();
				
			}
		}
	}
} 


void MainWin::runOrAlpha(){
	//Enter code for OR
	string input = searchInput -> text().toStdString();
	vector<string> search;
	vector<WebPage*> orAlpha;
	int wordCount = 0; 

	//Cleans up the user input
	bool clean = cleanUp(input, wordCount, search);
	displayAdsOr(search);
	if (clean == false){
		resultsList -> clear();
		cout << "Please follow the format of comma separation and period termination: " << endl; 
		cout << "Example: Word, word, lastword." << endl;
	}
	else{
		//If they try to find the or of one word
		if(wordCount < 2){
			cout << "You didn't enter enough words" << endl;
			resultsList -> clear();
		}
		else{
			vector< Set<WebPage*>* > unions;
			for (unsigned int i =0; i < search.size(); i++){
				Set <WebPage*>* match = new Set<WebPage*>; 
				pointerList.push_back(match);
				string temp = search[i];
				for (unsigned int j =0; j < pageNames.size(); j++){
					if(pageNames[j] -> allWords().contains(temp) == true){
						match -> insert(pageNames[j]);
					}
				}
				if (match -> size() != 0){
					unions.push_back(match);
				}
			}
			if(unions.size() > 0){
				Set<WebPage*> join = (*unions[0]);
				for (unsigned int i = 1; i < unions.size(); i++){
					join = join.setUnion(*unions[i]);
				}

				expandSet(join, orAlpha);
				expandAlpha(orAlpha);

				mergeSort<WebPage*, AlphaStrComp<WebPage*> > obj;
				AlphaStrComp <WebPage*>  comp1; 
				obj.merge_sort(orAlpha, comp1); //alphabetically sort it 
				
				displayResults(orAlpha);
				
			}
			else{
				cout << "No results found" << endl;
				resultsList -> clear();
			}
		} 
	}

} 	

//searches based on page rank value 
void MainWin::runSearchPage(){
	//Enter code for single word here
	string input = searchInput -> text().toStdString();
	lowerCase(input);

	//Random easter eggs
	if(input == "green"){
		setStyleSheet("background-color: green;");
	}
	if (input == "purple"){
		setStyleSheet("background-color: purple;");
	}
	if (input == "joke"){
		cout << "It told a joke" << endl;
		DefWin* tempWindow = new DefWin("joke");
		tempWindow -> show();
	}

	displayAds(input);
	Set<WebPage*> match;
	vector<WebPage*> mylist;
	bool matches = false;
	for(unsigned int i = 0; i < pageNames.size(); i++){
		if(pageNames[i] -> allWords().contains(input) == true){
			match.insert(pageNames[i]);
			matches = true;
		}
	}//end for pageNames
	//If it's not there
	
	if (matches == false){
		cout << "This search does not yield results" << endl;
	}//end matches = false

	expandSet(match, mylist);
	runPageVal(mylist);

	mergeSort<WebPage*, pageRank<WebPage*> > obj;
	pageRank <WebPage*>  comp1; 
	obj.merge_sort(mylist, comp1); //alphabetically sort it 

	flipVec(mylist);

}

void MainWin::runAndPage(){
	//Enter code for AND
	string input = searchInput -> text().toStdString();
	vector<string> search;
	vector<WebPage*> andPage; 
	int wordCount = 0; 
	//Cleans up the user input
	bool clean = cleanUp(input, wordCount, search);
	displayAdsOr(search);
	if (clean == false){
		resultsList -> clear();
		cout << "Please follow the format of comma separation and period termination: " << endl; 
		cout << "Example: Word, word, lastword." << endl;
	}
	else{
		if(wordCount < 2){
			cout << "You didn't enter enough words" << endl;
			resultsList -> clear();
		}
		else{
			map<string, Set<WebPage*>*> intersects;
			for (unsigned int i =0; i < search.size(); i++){
				Set <WebPage*>* match = new Set<WebPage*>;
				pointerList.push_back(match);
				string temp = search[i]; 
				//If the words in there, throw page into my set! 

				for (unsigned int j =0; j < pageNames.size(); j++){
					if(pageNames[j] -> allWords().contains(temp) == true){
						match -> insert(pageNames[j]);
					}
				}
				//Now add that set into my map with the word
				intersects.insert(pair<string, Set<WebPage*>*>(search[i], match));
			}

			Set<WebPage*> cross = (*intersects.at(search[0]));

			for (unsigned int i = 1; i < search.size(); i++){
				cross = cross.setIntersection(*intersects.at(search[i]));
			}

			for (Set<WebPage*>::iterator it=cross.begin(); it!=cross.end(); ++it){ //copy the set into a vector
				WebPage* addIt = *it;
				andPage.push_back(addIt);
			}		
			runPageVal(andPage);

			mergeSort<WebPage*, pageRank<WebPage*> > obj;
			pageRank <WebPage*>  comp1; 
			obj.merge_sort(andPage, comp1); //alphabetically sort it 

			flipVec(andPage);
		}
	}

} 

void MainWin::runOrPage(){
	//Enter code for OR
	string input = searchInput -> text().toStdString();
	//cout << input << endl;
	vector<string> search;
	vector<WebPage*> orPage;
	int wordCount = 0; 

	//Cleans up the user input
	bool clean = cleanUp(input, wordCount, search);
	displayAdsOr(search);

	if (clean == false){
		resultsList -> clear();
		cout << "Please follow the format of comma separation and period termination: " << endl; 
		cout << "Example: Word, word, lastword." << endl;
	}//end if clean 
	else{
		//If they try to find the or of one word
		if(wordCount < 2){
			cout << "You didn't enter enough words" << endl;
			resultsList -> clear();
		}
		else{
			vector< Set<WebPage*>* > unions;
			for (unsigned int i =0; i < search.size(); i++){
				Set <WebPage*>* match = new Set<WebPage*>; 
				pointerList.push_back(match);
				string temp = search[i];
				for (unsigned int j =0; j < pageNames.size(); j++){
					if(pageNames[j] -> allWords().contains(temp) == true){
						match -> insert(pageNames[j]);
					}
				}
				if (match -> size() != 0){
					unions.push_back(match);
				}
			} //end for

			if(unions.size() > 0){
				Set<WebPage*> join = (*unions[0]);
				for (unsigned int i = 1; i < unions.size(); i++){
					join = join.setUnion(*unions[i]);
				}

				for (Set<WebPage*>::iterator it=join.begin(); it!=join.end(); ++it){ //copy the set into a vector
					WebPage* addIt = *it;
					orPage.push_back(addIt);
				}
				if(orPage.size() > 0){
					runPageVal(orPage);
				}
				
				mergeSort<WebPage*, pageRank<WebPage*> > obj;
				pageRank <WebPage*>  comp1; 
				obj.merge_sort(orPage, comp1); //alphabetically sort it 


				flipVec(orPage);
			}//end if union size > 0  
		}//end smaller else
	}// end else

} 	

void MainWin::expandSet(Set<WebPage*>& match, vector <WebPage*>& mylist){
	for (Set<WebPage*>::iterator it=match.begin(); it!=match.end(); ++it){ //copy the set into a vector
		WebPage* addIt = *it;
		mylist.push_back(addIt);
	}
}

void MainWin::expandAlpha(vector <WebPage*>& alphaVec){
	Set<WebPage*> results; Set<WebPage*> originalResults; 
	for (unsigned int i = 0; i < alphaVec.size(); i++){
		results.insert(alphaVec[i]);
		originalResults.insert(alphaVec[i]);

	}

	//Set with the results of the word search 
	for (vector<WebPage*>::iterator vecIt = alphaVec.begin(); vecIt != alphaVec.end(); ++vecIt){
		WebPage* temp = *vecIt;
		
		results = results.setUnion(originalResults); //forgot to include the original...
		results = results.setUnion(temp -> allOutgoingLinks());
		results = results.setUnion(temp -> allIncomingLinks());
	}
	alphaVec.clear();
	for (Set<WebPage*>::iterator copy = results.begin(); copy != results.end(); ++copy){
		WebPage* temp = *copy;

		alphaVec.push_back(temp);
	}
}

void MainWin::flipVec(vector<WebPage*>& flipIt){
	vector<WebPage*> flipVal;
		for (int i = flipIt.size() - 1; i >= 0; i--){
			flipVal.push_back(flipIt[i]);
		}
		if(flipIt.size() > 0){
			vector<WebPage*> flipVal;
			for (int i = flipIt.size() - 1; i >= 0; i--){
				flipVal.push_back(flipIt[i]);
			}
			displayResults(flipVal);
		}
		else{
				cout << "No results found" << endl;
				resultsList -> clear();		
		}
}
bool MainWin::readAds(string adfile){
	ifstream ifile(adfile); 
	int numCompanies; 
	ifile >> numCompanies; 
	
	for(int i = 0; i < numCompanies; i++){
		Ad* tempAd = new Ad();
		string keyword; 
		ifile >> keyword; 
		lowerCase(keyword); 
		tempAd -> setKeyWord(keyword);
		double bid; 
		ifile >> bid; 
		tempAd -> setScore(bid);
		
		string getInfo; 
		getline(ifile, getInfo);
	
		tempAd -> setName(getInfo);
		adNames.push_back(tempAd);	
	}

	mergeSort<Ad*, AlphaStrComp<Ad*> > obj;
	AlphaStrComp <Ad*>  comp1; 
	obj.merge_sort(adNames, comp1); //alphabetically sort it 

	for (unsigned int i = 0; i < adNames.size(); i++){
		//Add the individual companies to the map 
		pair<string, double> tempMapEntry(adNames[i] -> filename(), 0.0);
		billTotal.insert(tempMapEntry);
	}

	return true; 
}
void MainWin::displayAds(string keyWord){
	adsList -> clear();
	vector <Ad*> organize; 
	
	for(unsigned int i = 0; i < adNames.size(); i++){
		if(adNames[i] -> getKey() == keyWord){
			organize.push_back(adNames[i]);
		}
	}
	mergeSort<Ad*, bidRank<Ad*> > obj;
	bidRank <Ad*>  comp1; 
	obj.merge_sort(organize, comp1); //sort it by rank

	miniSort(0, organize.size(), 0, organize);

	for(unsigned int i = 0; i < organize.size(); i++){
		QListWidgetItem* temp = new QListWidgetItem(QString::fromStdString(organize[i] -> filename())); //this needs to be delete somewhere
		adsList -> insertItem(0, temp);
	}
}
void MainWin::displayAdsOr(vector<string> keyWord){
	for(unsigned int i = 0; i < keyWord.size(); i++){
		cout << "This is the keyword " << keyWord[i] << endl;
	}
	adsList -> clear();
	vector <Ad*> organize; 
	
	for(unsigned int i = 0; i < adNames.size(); i++){
		
		Ad* keep = adNames[i];
		for (unsigned int j = 0; j < keyWord.size(); j++){
			
			if(adNames[i] -> getKey() == keyWord[j]){
				
				bool inOrg = false;
				for(unsigned int k = 0; k < organize.size(); k++){
					if(adNames[i] -> filename() == organize[k] -> filename()){
						inOrg = true;
						if(keep -> getScore() <= organize[k] -> getScore()){
							keep = organize[k]; 
							organize[k] = keep;
						}
						else{
							organize[k] = keep;
							keep = organize[k];
							//Make keep the bigger number for the rest of comparisons
						}
					}
				}//end check if it has multiple bids
				if(inOrg == false){
					organize.push_back(keep);
				}
			}//end if there's the key 
		}
	}
	mergeSort<Ad*, bidRank<Ad*> > obj;
	bidRank <Ad*>  comp1; 
	obj.merge_sort(organize, comp1); //alphabetically sort it 

	miniSort(0, organize.size(), 0, organize);
	
	for(unsigned int i = 0; i < organize.size(); i++){
		QListWidgetItem* temp = new QListWidgetItem(QString::fromStdString(organize[i] -> filename())); //this needs to be delete somewhere
		adsList -> insertItem(0, temp);
	}
}

vector<Ad*>& MainWin::miniSort(int start, int end, int done, vector<Ad*>& organize){
	if(done == end){
		return organize;
	}
	else{
		for (unsigned int i = 0; i < organize.size(); i++){
			unsigned int max = i + 1; //Compare to thing in front of it if it exists
			if(max != organize.size()){
				if(organize[i] -> getScore() == organize[max] -> getScore()){
					//Should be swapped if out of order!
					if(organize [i] -> filename() < organize[max] -> filename()){
						Ad* rearrange = organize[max];
						organize[max] = organize[i];
						organize[i] = rearrange;
					}
				}
			}
		}
		done++;
		return miniSort(start+1, end, done, organize);
	}
}