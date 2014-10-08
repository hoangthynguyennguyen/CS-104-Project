#include "profile.h"
#include <sstream>
#include <string>
#include <exception>
#include <list>
#include <QApplication> 
#include "../web/web.h"

using namespace std; 


Profile::Profile(User* username){
	setWindowTitle(QString::fromStdString(username -> getName() + "'s profile"));
	filename = new QLabel(QString::fromStdString(username -> getName()));
	_topPages = new QLabel("Top Pages");
	_viewHistory = new QLabel("Web History");
	_clickedAds = new QLabel("Visited Companies");
	viewHistory = new QListWidget();
	clickedAds = new QListWidget();
	topPages = new QListWidget();
	searchLayout = new QHBoxLayout;
	boxLay = new QVBoxLayout;
	adsBox = new QVBoxLayout;
	btnClose = new QPushButton("&Close");
	
	myname = username -> getName();
	myUser = username;

	
	
	centerWidget = new QWidget(this); //Idk what this actually does....
	centerWidget -> setLayout(searchLayout);
	this -> setCentralWidget(centerWidget);

	boxLay -> addWidget(_topPages, 0);
	boxLay -> addWidget(topPages, 0);
	boxLay -> addWidget(_viewHistory, 0);
	boxLay -> addWidget(viewHistory, 0);
	
	adsBox -> addWidget(_clickedAds, 0);
	adsBox -> addWidget (clickedAds, 0);
	adsBox->addWidget(btnClose);
	

	searchLayout -> addLayout(adsBox, 0);
	searchLayout -> addLayout(boxLay, 0);

	connect(btnClose, SIGNAL(clicked()), this, SLOT(closeWindow()));

	fillPages();
	fillAds();
}
Profile::Profile(){
	
}
Profile::~Profile(){
	
}

void Profile::closeEvent(QCloseEvent* event)
{
	emit closeProfile();
	event->accept();
}


void Profile::fillAds(){
	set<string> tempAds = myUser -> getCompanies();
	for(set<string>::iterator it = tempAds.begin(); it != tempAds.end(); ++it){
		string temp = *it; 
		QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(temp));
		clickedAds -> addItem(newItem);
	}
}
void Profile::fillPages(){
	clearPages();
	tempList = myUser -> getMostVisited();

	int numRows = 0;
	for(unsigned int i = 0; i< tempList.size(); i++){
		QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(tempList[i]));
		topPages -> insertItem(numRows, newItem);
		numRows++;
	}
}
void Profile::addHistory(std::string justViewed){
	QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(justViewed));
	viewHistory -> addItem(newItem);
}
void Profile::clearPages(){
	topPages -> clear();
	clickedAds -> clear();
	
	while(!tempList.empty()){
		tempList.pop_back();
	}
}
void Profile::refreshPage(std::string name){
	setWindowTitle(QString::fromStdString(name));
	clearPages();
	//Add everything back in
	fillPages();
	fillAds();
}

void Profile::closeWindow()
{
	this->hide();
	emit closeProfile();
}