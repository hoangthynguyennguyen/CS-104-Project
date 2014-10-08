#ifndef CREATEACCOUNT_H_
#define CREATEACCOUNT_H_

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <string>
#include <QMetaObject>
#include <QMessageBox>
#include <iostream>

class createaccount : public QMainWindow
{
	Q_OBJECT

	public:
		createaccount(QWidget* parent = 0);
		~createaccount();

	public slots:
		void checkInput(); //checks the input and passes it back to main login window with returnAccount()
		void closeWindow();

	signals:
		void returnAccount(std::string userOut, std::string passOut); //returns a new account to the main window

	private:	
		QLabel* userLabel;
		QLabel* passLabel;
		QLabel* passCheckLabel;

		QLineEdit* username;
		QLineEdit* password;
		QLineEdit* passCheck;

		QPushButton* btnSubmit;
		QPushButton* btnClose;

		QFormLayout* window;
		QWidget* centerWidget;

};

#endif