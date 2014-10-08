#include "searchwin.h"
#include <sstream>
#include <string>
#include <exception>
#include <list>
#include <QApplication> 
#include "../web/web.h"

using namespace std;

SearchWin::SearchWin(string input, QWidget *parent) : QMainWindow(parent){

	//Allocate memory
	setWindowTitle(QString::fromStdString(input));
	fileName = new QLabel(QString::fromStdString(input));
	outGoing = new QLabel("Outgoing Links");
	inComing = new QLabel("Incoming Links");
	incomingLinks = new QListWidget();
	outgoingLinks = new QListWidget();
	displayPage = new QTextEdit(QString::fromStdString("Default text"));
	searchLayout = new QHBoxLayout;
	boxLay = new QVBoxLayout;
	leftSide = new QVBoxLayout;

	//Set the displayPage so that it's fixed 
	displayPage -> setReadOnly(true);

	QListWidgetItem* newItem = new QListWidgetItem("Here you go"); 
	linkPtrs.push_back(newItem);
	outgoingLinks -> insertItem(0, newItem);
	//Setup layout
	centerWidget = new QWidget(this); //Idk what this actually does....
	centerWidget -> setLayout(searchLayout);
	this -> setCentralWidget(centerWidget);

	//add widget to the layout

	boxLay -> addWidget(inComing, 0);
	boxLay -> addWidget(incomingLinks, 0);
	boxLay -> addWidget(outGoing, 0);
	boxLay -> addWidget(outgoingLinks, 0);
	leftSide -> addWidget(fileName, 0);
	leftSide -> addWidget(displayPage, 0);
	searchLayout -> addLayout(leftSide, 0);
	searchLayout -> addLayout(boxLay, 0);

	//connect buttons
	connect(outgoingLinks, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(outClicked()));
}


SearchWin::SearchWin(WebPage* fileWanted, vector<WebPage*> &pageNames, QWidget *parent) : QMainWindow(parent){
	
	string input = fileWanted -> filename();
	pageNamez = pageNames;
	string page = fileWanted -> allString();
	
	
	//Allocate memory
	setWindowTitle(QString::fromStdString(input));
	fileName = new QLabel(QString::fromStdString(input));
	outGoing = new QLabel("Outgoing Links");
	inComing = new QLabel("Incoming Links");
	incomingLinks = new QListWidget();
	outgoingLinks = new QListWidget();
	displayPage = new QTextEdit(QString::fromStdString("Default text"));
	searchLayout = new QHBoxLayout;
	boxLay = new QVBoxLayout;
	leftSide = new QVBoxLayout;

	//Set the displayPage so that it's fixed 
	displayPage -> setReadOnly(true);
	displayPage -> setPlainText(QString::fromStdString(page));
	
	//Setup layout
	centerWidget = new QWidget(this); //Idk what this actually does....
	centerWidget -> setLayout(searchLayout);
	this -> setCentralWidget(centerWidget);

	//add widget to the layout

	boxLay -> addWidget(inComing, 0);
	boxLay -> addWidget(incomingLinks, 0);
	boxLay -> addWidget(outGoing, 0);
	boxLay -> addWidget(outgoingLinks, 0);
	leftSide -> addWidget(fileName, 0);
	leftSide -> addWidget(displayPage, 0);
	searchLayout -> addLayout(leftSide, 0);
	searchLayout -> addLayout(boxLay, 0);

	
	//Fill in the list objects with links
	fillLinks(fileWanted);
	
	//connect buttons
	connect(outgoingLinks, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(outClicked()));
	connect(incomingLinks, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(inClicked()));
	
}

SearchWin::~SearchWin(){
	
}
void SearchWin::refreshPage(string _file){
	setWindowTitle(QString::fromStdString(_file));
	displayPage -> clear();
	incomingLinks -> clear();
	outgoingLinks -> clear();
	fileName -> clear();
	fileName -> setText(QString::fromStdString(_file));
	displayPage -> setPlainText(QString::fromStdString("Reset text"));
	QListWidgetItem* newItem = new QListWidgetItem("Here's a new one"); 
	linkPtrs.push_back(newItem);
	outgoingLinks -> insertItem(0, newItem);
}

void SearchWin::refreshPage(WebPage* fileSelected){
	string input = fileSelected -> filename();
	setWindowTitle(QString::fromStdString(input));
	displayPage -> clear();
	incomingLinks -> clear();
	outgoingLinks -> clear();
	fileName -> clear();
	fileName -> setText(QString::fromStdString(fileSelected -> filename()));
	displayPage -> setPlainText(QString::fromStdString(fileSelected -> allString()));
	fillLinks(fileSelected);
}

void SearchWin::outClicked(){
	displayPage -> clear();
	fileName -> clear();
	string linkLabel = outgoingLinks -> currentItem() -> text().toStdString();
	fileName -> setText(QString::fromStdString(linkLabel));
	setWindowTitle(QString::fromStdString(linkLabel));
	WebPage* fileSelected = NULL;
	for(unsigned int i = 0; i < pageNamez.size(); i++){
		if(pageNamez[i] -> filename() == linkLabel){
			fileSelected = pageNamez[i];
		}
	}
	displayPage -> setPlainText(QString::fromStdString(fileSelected -> allString())); 
	fillLinks(fileSelected);
	

} //Display the outgoing link that was clicked 
void SearchWin::inClicked(){
	displayPage -> clear();
	fileName -> clear();
	string linkLabel = incomingLinks -> currentItem() -> text().toStdString();
	fileName -> setText(QString::fromStdString(linkLabel));
	setWindowTitle(QString::fromStdString(linkLabel));
	WebPage* fileSelected = NULL;
	for(unsigned int i = 0; i < pageNamez.size(); i++){
		if(pageNamez[i] -> filename() == linkLabel){
			fileSelected = pageNamez[i];
		}
	}
	displayPage -> setPlainText(QString::fromStdString(fileSelected -> allString())); 
	fillLinks(fileSelected);

} //Display the incoming link that was clicked 
void SearchWin::fillLinks(WebPage* fileWanted){
	int numRows = 0;
	incomingLinks -> clear();
	outgoingLinks -> clear();
	Set<WebPage*> printIn = fileWanted -> allIncomingLinks();
	if(printIn.empty() != true){
		for(Set<WebPage*>::iterator pageIt = printIn.begin(); pageIt != printIn.end(); ++pageIt){
			WebPage* tempLink = *pageIt;
			QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(tempLink -> filename()));
			linkPtrs.push_back(newItem);
			incomingLinks -> insertItem(numRows ,newItem); 
			numRows++;
		}
	}
	Set<WebPage*> printOut = fileWanted -> allOutgoingLinks();
	if(printOut.empty() != true){
		numRows = 0;
		for(Set<WebPage*>::iterator pageOut = printOut.begin(); pageOut != printOut.end(); ++pageOut){
			WebPage* tempLinkz = *pageOut;
			QListWidgetItem* newItemz = new QListWidgetItem(QString::fromStdString(tempLinkz -> filename()));
			linkPtrs.push_back(newItemz);
			outgoingLinks -> insertItem(numRows ,newItemz); 
			numRows++;
		}
	}
}
