#include "popup.h"
#include <string> 
#include <QApplication> 

using namespace std; 

Popup::Popup(Ad* adName, QWidget *parent) : QMainWindow(parent){
	setWindowTitle(QString::fromStdString(adName -> filename()));
	filename = new QLabel(QString::fromStdString(adName -> filename()));
	popLayout = new QVBoxLayout; 
	displayPage = new QTextEdit(QString::fromStdString("You have opened the page for " + adName-> filename()));

	displayPage -> setReadOnly(true);

	centerWidget = new QWidget(this);
	centerWidget -> setLayout(popLayout);
	this -> setCentralWidget(centerWidget);
	popLayout -> addWidget(filename, 0);
	popLayout -> addWidget(displayPage, 0);
}
Popup::~Popup(){

}
void Popup::refreshPop(Ad* aName){
	setWindowTitle(QString::fromStdString(aName -> filename()));
	displayPage -> clear();
	filename -> clear(); 
	displayPage -> setPlainText(QString::fromStdString("You have opened the page for " + aName -> filename()));
	filename -> setText(QString::fromStdString(aName -> filename()));
}