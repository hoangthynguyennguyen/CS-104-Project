#include "createaccount.h"
#include <QApplication>
using namespace std;

createaccount::createaccount(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle(QString::fromStdString("Create an Account!"));
	//declare labels
	userLabel = new QLabel(QString::fromStdString("Enter a username:"));
	passLabel = new QLabel(QString::fromStdString("Enter a password:"));
	passCheckLabel = new QLabel(QString::fromStdString("Re-enter your password:"));
	//declare buttons
	btnClose = new QPushButton("&Close");
	btnSubmit = new QPushButton("&Submit");
	//declare text boxes
	username = new QLineEdit();
	password = new QLineEdit();
	passCheck = new QLineEdit();

	window = new QFormLayout;

	centerWidget = new QWidget(this);
	centerWidget -> setLayout(window);
	this -> setCentralWidget(centerWidget);
	//create layout
	window->addRow(userLabel, username);
	window->addRow(passLabel, password);
	window->addRow(passCheckLabel, passCheck);
	window->addRow(btnSubmit, btnClose);

	connect(btnClose, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(btnSubmit, SIGNAL(clicked()), this, SLOT(checkInput()));
}

createaccount::~createaccount() {}

void createaccount::checkInput() //checks the input and passes it back to main window if passwords match
{
	string name = username->text().toStdString();
	string pass = password->text().toStdString();
	string check = passCheck->text().toStdString();
	if(name.empty())
	{
		QMessageBox::information(this, "Account creation", "You must enter a username!");
	}
	else
	{
		if(pass.empty())
		{
			QMessageBox::information(this, "Account creation", "You must enter a password!");
		}
		else
		{
			if(pass == check)
			{
				emit returnAccount(name, pass);
				closeWindow();
			}
			else
			{
				QMessageBox::information(this, tr("Account creation"), tr("Passwords do not match"));
			}
		}
	}
}

void createaccount::closeWindow()
{
	this->close();
}