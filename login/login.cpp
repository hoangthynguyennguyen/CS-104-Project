#include "login.h"
#include "createaccount.h"
#include <iostream>
#include <QApplication>
using namespace std;

login::login(std::string input, std::string adfile, std::string billfile, QWidget* parent) : QMainWindow(parent)
{
	//reads all existing accounts into the map upon startup
	_input = input; 
	_adfile = adfile;
	_billfile = billfile;
	MainWinOpened = false;
	accounts = new map<string, string>();
	fstream myFile;
	myFile.open("login/accountInfo.txt", fstream::in);
	string tempS = "";
	while(getline(myFile, tempS))
	{
		stringstream ss;
		string name;
		ss << tempS;
		ss >> name;
		string pass;
		ss << tempS;
		ss >> pass;
		pass = pass.substr(0, pass.size() - name.size()); //not sure why it's appending things, fixed bug but not problem
		accounts->insert(make_pair(name, pass));
	}

	setWindowTitle(QString::fromStdString("Login!"));	
	//declare labels
	userLabel = new QLabel(QString::fromStdString("Username:"));
	passLabel = new QLabel(QString::fromStdString("Password:"));
	//declare buttons
	btnSubmit = new QPushButton("&Submit");
	btnQuit = new QPushButton("&Quit");
	btnCreate = new QPushButton("&Create Account");
	//declare line text boxes
	username = new QLineEdit();
	password = new QLineEdit();
	password->setEchoMode(QLineEdit::Password);
	winLayout = new QFormLayout;
	//create the layout
	winLayout -> addRow(userLabel, username);
	winLayout -> addRow(passLabel, password);
	winLayout -> addRow(btnSubmit, btnQuit);
	winLayout -> addRow(btnCreate);

	centerWidget = new QWidget(this);
	centerWidget -> setLayout(winLayout);
	this -> setCentralWidget(centerWidget);
	//connections
	connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit())); //quits the program
	connect(btnCreate, SIGNAL(clicked()), this, SLOT(create())); //allows user to create an account
	connect(btnSubmit, SIGNAL(clicked()), this, SLOT(checkInfo()));
	connect(this, SIGNAL(success()), this, SLOT(openMainWin()));
}

login::~login() {
	if (MainWinOpened == true){
		delete tempWindow;
	}
}

void login::create()
{
	createaccount* temp = new createaccount(this);
	temp->show();
	connect(temp, SIGNAL(returnAccount(std::string, std::string)), this, SLOT(write(std::string, std::string))); //gets the info back
	//from the account creation window and passes it to the write function
}

void login::write(std::string userIn, std::string passIn)
{
	if(accounts->find(userIn) == accounts->end()) //check to see if account already exists
	{
		fstream myFile("login/accountInfo.txt", fstream::out | ofstream::app); //write to end of existing file
		myFile << userIn << "\t" << passIn << endl;
		accounts->insert(make_pair(userIn, passIn));
		myFile.close();
	}
	else
	{
		QMessageBox::information(this, tr("Account creation"), tr("This username already exists!"));
		create();
	}
}

void login::checkInfo()
{
	string name = username->text().toStdString();
	string pass = password->text().toStdString();
	map<string, string>::iterator found = accounts->find(name); //check if username exists
	if(found == accounts->end())
	{
		QMessageBox::information(this, "login", "This username doesn't exist!");
	}
	else
	{
		string expected = found->second; //password that corresponds with the username
		if(pass == expected) //check to see if correct password 
		{
			emit success();
			this -> hide();
		}
		else
		{
			QMessageBox::information(this, tr("Login"), tr("Incorrect password!"));
		}
	}
}
void login::openMainWin(){
	tempWindow = new MainWin(_input, _adfile, _billfile, username->text().toStdString(), 0);
	MainWinOpened = true;

	tempWindow -> show();
}