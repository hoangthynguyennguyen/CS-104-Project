#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QMainWindow> 
#include <QPushButton> 
#include <QPushButton>
#include <string> 
#include <QString>
#include <QMessageBox>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel> 
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include "searchwin.h"
#include <list>
#include <iostream>
#include <stdexcept>  
#include "../lib/set2.h"
#include "../web/web.h"
#include <vector>
#include <map>
#include "../lib/mergesort2.h" //trying my own mergesort
#include "popup.h"
#include <deque>
#include "../web/ad.h"
#include "profile.h"
#include "defwin.h"
#include "../user/user.h"


//helper functions go here 

class MainWin : public QMainWindow 
{
	Q_OBJECT 

	public: 
		//MainWin(QWidget *parent = 0);
		MainWin(std::string input, string adfile, string billfile, string username, QWidget *parent = 0);
		~MainWin(); 
		std::vector<WebPage*> pageNames; //want searchWin to access it 
		std::vector<Ad*> adNames;
		std::map<string, double> billTotal;
	private slots: 
		void displayResults(vector<WebPage*> cross);
		void openNewWin(); //Open the results window some how
		void openPopUp();
		void openProfile();
		void runSearchPage(); //do ze search with single word
		void runAndPage(); //Run the search with AND
		void runOrPage(); //Run the search with OR
		void runSearchAlpha(); //do ze search with single word
		void runAndAlpha(); //Run the search with AND in alphabetical order
		void runOrAlpha(); //Run the search with OR in alphabetical order 
		void runPageVal(vector<WebPage*>& pageName); //Create the pagevalues for specific pagenames
		void needToClose();
		
		
	private: 
		QLabel *fileName; //to display the name of file at the top? 
		QLabel *ads;
		QPushButton *btnQuit; //button to quit the application 
		QPushButton *btnSearch; //button to run the search with single word 
		QPushButton *btnAnd;  //Button to run the AND function with alphabet
		QPushButton *btnOr; //Button to run the OR function with alphabet
		QPushButton *btnAndPage; //Button to sort pageRank
		QPushButton *btnOrPage; //Button to do by pagerank value 
		QPushButton *btnSearchPage; //Button to do by pagerank value
		QPushButton *btnViewPro;  
		QLineEdit *searchInput; //area to type in the query
		QListWidget *resultsList; //to display the list of results
		QListWidget *adsList; //to display the list of results
		QVBoxLayout *winLayout; //This is the display of the actual window?
		QHBoxLayout *buttLayout; //This is the display of my buttons
		QHBoxLayout *buttLayout2; //This is the display of my buttons
		QWidget *centerWidget; //Something about the central widget though 
		User* currentUser;
		std::list<SearchWin* > lookUpList;
		std::list<QListWidgetItem* > resultList;
		std::vector< Set<WebPage*>* > pointerList;
		std::deque<Popup*> adList;
		std::deque<Profile*> proList;
		Profile* temp;
		bool windowOpen;
		bool adOpen;
		bool profileOpen;
		std::string indexName; //name of the original file input 
		std::string outFileName; //name of the place to write bill
		std::string _userName;
		//Functions will go here from project_laijessi.cpp
		bool openIndex(std::string);
		bool getFiles(std::ifstream &, std::vector<WebPage*> &);
		void lowerCase(std::string&);
		bool cleanUp(std::string& , int&, std::vector<string>&);
		void getLinks(WebPage*, std::vector<WebPage*>&); 
		void setIndexes();
		void expandSet(Set<WebPage*>&, vector <WebPage*>&);
		void expandAlpha(vector<WebPage*>&);
		void flipVec(vector<WebPage*>& flipIt);
		bool readAds(std::string);
		void displayAds(std::string);
		void displayAdsOr(std::vector<string>);
		vector<Ad*>& miniSort(int, int, int, vector<Ad*>&);



};


#endif 