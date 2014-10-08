#ifndef SEARCHWIN_H
#define SEARCHWIN_H

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
#include "../web/web.h"
#include <vector>
#include <list>

class SearchWin : public QMainWindow
{
	Q_OBJECT
public:
	SearchWin(std::string input, QWidget *parent = 0); //input will be the words searched for
	SearchWin(WebPage* fileWanted, vector<WebPage*> &pageNames, QWidget *parent = 0); 
	~SearchWin();
	void refreshPage(std::string _file);
	void refreshPage(WebPage* fileSelected);
private slots:
	void outClicked(); //Display the outgoing link that was clicked 
	void inClicked(); //Display the incoming link that was clicked 


private:
	QLabel *fileName; //Display the filename
	QLabel *outGoing; // Display that it's the outgoing links
	QLabel *inComing; //Display that it's the incoming links
	QListWidget *incomingLinks; //display incoming links
	QListWidget *outgoingLinks; //display outgoing links
	QTextEdit *displayPage; //Display the text in this link 
	QHBoxLayout *searchLayout; //This is the display of the actual window
	QVBoxLayout *boxLay; //This is the display of the boxes in the window
	QVBoxLayout *leftSide; //display + filename
	QWidget *centerWidget;
	std::list<QListWidgetItem* > linkPtrs;
	std::vector<WebPage*> pageNamez;
	void fillLinks(WebPage*);


};

#endif
