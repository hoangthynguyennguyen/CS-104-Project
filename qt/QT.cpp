#include <qapplication.h>
#include "mainwin.h"
//#include "web.h"

int main(int argc, char *argv[])
{
	if (argc != 4){
		cout << "You have not entered the command line properly" << endl;
		return -1;
	}

	QApplication app(argc, argv);  

	//MainWin window;
	MainWin window(argv[1], argv[2], argv[3]);

	//window.setWindowTitle("Search For Words");
	window.setWindowTitle(argv[1]);
	window.show();

	return app.exec();
}


