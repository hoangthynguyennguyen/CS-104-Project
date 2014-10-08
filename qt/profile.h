#ifndef PROFILE_H
#define PROFILE_H 
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
#include <QCloseEvent>
#include <QLabel> 
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include "../web/web.h"
#include <vector>
#include "../web/ad.h"
 #include <QPixmap>
#include <QIcon>
#include "../user/user.h"

class Profile: public QMainWindow
{
	Q_OBJECT 
public: 
	Profile(string username);
	Profile(User* username);
	Profile();
	~Profile();
	//Profile(User* username);
	void refreshPage(std::string);
	void fillAds();
	void fillPages();
	void addHistory(std::string);
	void clearPages();

public slots:
	void closeWindow();

signals:
	void closeProfile();
private: 
	QLabel *filename;
	QLabel *_topPages;
	QLabel *_viewHistory; 
	QLabel *_clickedAds;
	QListWidget *clickedAds; //display incoming links
	QListWidget *topPages; //display outgoing links
	QListWidget *viewHistory; //display outgoing links
	QHBoxLayout *searchLayout; //This is the display of the actual window
	QVBoxLayout *boxLay; //This is the display of the boxes in the window
	QVBoxLayout *adsBox;
	QWidget *centerWidget;
	std::string myname;
	User* myUser;
	vector<std::string> tempList;
	QPushButton* btnClose;

	void closeEvent(QCloseEvent* event);

	
};

#endif