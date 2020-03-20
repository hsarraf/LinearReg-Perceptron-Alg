/////////////////////////////////
//Regression - Classification////
//main.cpp///////////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////

#include "MainWindow.h"

int main(int argc, char **argv) {
	MakeMainWindow(argv[0]);
	__mainWindow->show(argc, argv);
	return Fl::run();
}
