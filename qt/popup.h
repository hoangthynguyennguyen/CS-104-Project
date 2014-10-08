#ifndef POPUP_H
#define POPUP_H
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
#include "../web/ad.h"

class Popup: public QMainWindow
{
	Q_OBJECT
public:
	Popup(Ad* adName, QWidget *parent = 0);
	~Popup();
	void refreshPop(Ad* aName);
private:
	QLabel *filename;
	QVBoxLayout *popLayout; //This is the display of the actual window
	QTextEdit *displayPage; //Display the text in this link 
	QWidget *centerWidget;
};
#endif
