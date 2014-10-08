#include "login.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 4){
		cout << "You have not entered the command line properly" << endl;
		return -1;
	}

	
    QApplication a(argc, argv);
    login window(argv[1], argv[2], argv[3]);
  
    window.show();
    return a.exec();
}