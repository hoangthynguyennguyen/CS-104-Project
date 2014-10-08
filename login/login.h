#ifndef LOGIN_H_
#define LOGIN_H_

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <string>
#include <QString>
#include <QFormLayout>
#include <QSignalMapper>
#include <map>
#include <sstream>
#include <fstream>
#include "../qt/mainwin.h"

class login : public QMainWindow
{
	Q_OBJECT

	public:
		login(std::string input, std::string adfile, std::string billfile, QWidget* parent = 0);
		~login();

	private slots:
		void create();	
		void write(std::string userIn, std::string passIn);
		void checkInfo();
		void openMainWin();

	signals:
		void success();

	
	private:
		QLabel* topdisplay; //to display text at top?
		QLineEdit* username; //to take in the username
		QLineEdit* password; //to take in the password
		QLabel* userLabel;
		QLabel* passLabel;
		QPushButton* btnQuit; //quit button
		QPushButton* btnSubmit; //submit button
		QPushButton* btnCreate;
		std::map<std::string, std::string>* accounts; //holds the account info
		QFormLayout* winLayout;
		QWidget* centerWidget;
		MainWin* tempWindow;
		std::string _input;
		std::string _adfile;
		std::string _billfile;
		bool MainWinOpened;
};

#endif