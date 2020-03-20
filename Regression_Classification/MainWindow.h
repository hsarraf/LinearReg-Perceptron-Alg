/////////////////////////////////
//Regression - Classification////
//MainWindow.H///////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////


#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Help_Dialog.H>

#include "Regression.h"
#include "KNN.h"
#include "Perceptron.h"
#include "DataSample.h"
#include "UIConfig.h"

// UI Widgets
//
Fl_Slider *_dataSetCountSlider;		
Fl_Button *_clearScreenButton;
// Rgression
//
Fl_Slider *_dataSetNoiseXSlider_Rgr;			
Fl_Slider *_dataSetNoiseYSlider_Rgr;			
Fl_Button *_dataSetGenButton_Rgr;				
Fl_Button *_computeRegressionButton;
// KNN
//
Fl_Slider *_dataSetPercent_KNN;
Fl_Slider *_dataSetExtentionCls1_KNN;
Fl_Slider *_dataSetExtentionCls2_KNN;
Fl_Button *_dataSetGenButton_KNN;				
Fl_Button *_generateDataSample_KNN;				
Fl_Slider *_sampleSlider_KNN;
Fl_Button *_computeKNN;							
// Perceptron
//
Fl_Slider *_thresholdSlider_Prp;
Fl_Slider *_learningRateSlider_Prp;
Fl_Button *_computePerceptronButton;


// Graph Window definition
//
class GraphWindow : public Fl_Double_Window {
public:
	GraphWindow(int x = 0, int y = 0, int w = 0, int h = 0, const char *l = 0)
		: Fl_Double_Window(x, y, w, h, l){}
private:
	void draw();
	int handle(int e);
}*_graphWindow;	// graph window


// override draw method to display canva
//
void GraphWindow::draw() {
	// force to draw
	//
	Fl_Double_Window::draw();

	// draw training samples
	//
	if (__trainingDataSet) {
		for (int i = 0; i < __trainingDataSize; i++) {
			int x = __trainingDataSet[i]._x * _graphWindow->w() / __Graph_W;
			int y = (__Graph_H - __trainingDataSet[i]._y) * _graphWindow->h() / __Graph_H;
			fl_color(__trainingDataSet[i]._clr);
			fl_circle(x, y, 2);
		}

		// draw regression line
		//
		if (__trainingDataSet[0]._id == -1) {
			fl_color(FL_WHITE);
			fl_line_style(0, 2);
			int x1 = __regression->_X1 * _graphWindow->w() / __Graph_W;
			int y1 = (__Graph_H - __regression->_M * __regression->_X1 - __regression->_H) * _graphWindow->h() / __Graph_H;
			int x2 = __regression->_X2 * _graphWindow->w() / __Graph_W;
			int y2 = (__Graph_H - __regression->_M * __regression->_X2 - __regression->_H) * _graphWindow->h() / __Graph_H;
			fl_line(x1, y1, x2, y2);
		}
	}

	// draw KNN test samples
	//
	if (__KNN->_dataSample) {
		int x = __KNN->_dataSample->_x * _graphWindow->w() / __Graph_W;
		int y = (__Graph_H - __KNN->_dataSample->_y) * _graphWindow->h() / __Graph_H;
		fl_color(__KNN->_dataSample->_clr);
		fl_circle(x, y, 5);
	}

	// draw perceptron training samples
	//
	if (__Perceptron->_trainingSamples.size() ) {
		for (int i = 0; i < __Perceptron->_trainingSamples.size(); i++) {
			int x = __Perceptron->_trainingSamples[i]._x * _graphWindow->w() / __Graph_W;
			int y = (__Graph_H - __Perceptron->_trainingSamples[i]._y) * _graphWindow->h() / __Graph_H;
			fl_color(__Perceptron->_trainingSamples[i]._clr);
			fl_circle(x, y, 5);
		}
	}
	// draw perceptron classifier line
	//
	if (__Perceptron->_weights[2]) {
		fl_color(FL_GREEN);
		fl_line_style(FL_DASH, 2);
		float m = -(float)__Perceptron->_weights[1] / __Perceptron->_weights[2];
		float h = -(float)__Perceptron->_weights[0] / __Perceptron->_weights[2];
		int x1 = 0;
		int y1 = (__Graph_H - h) * _graphWindow->h() / __Graph_H;
		int x2 = _graphWindow->w();
		int y2 = (__Graph_H - m * __Graph_W - h) * _graphWindow->h() / __Graph_H;
		fl_line(x1, y1, x2, y2);
	}
}

// event handler for mouse clicking
//
int GraphWindow::handle(int e) {
	if (e == FL_PUSH) {
		int x = Fl::event_x() * __Graph_W / w();
		int y = (_graphWindow->h() - Fl::event_y()) * __Graph_H / h();
		if (Fl::event_button() == FL_MIDDLE_MOUSE) {
			__KNN->InsertDataSample_KNN(x, y);
		}
		else if (Fl::event_button() == FL_LEFT_MOUSE) {
			__Perceptron->_trainingSamples.push_back(DataSample(x, y, 0, FL_RED));
		}
		else if (Fl::event_button() == FL_RIGHT_MOUSE) {
			__Perceptron->_trainingSamples.push_back(DataSample(x, y, 1, FL_BLUE));
		}
		_graphWindow->redraw();
	}
	return Fl_Window::handle(e);
}


// main window widget
//
class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char *l = 0)
		: Fl_Double_Window(w, h, l) {
		__regression = new Regression;
		__KNN = new KNN;
		__Perceptron = new Perceptron;
	}
	//static void UpdateDrawing();
private:
	// methods
	//
	void draw();
	void MakeMainWindow(const char *);
}*__mainWindow;	// main window



// redraw all widgets
//
void MainWindow::draw() {
	Fl_Double_Window::draw();
	_graphWindow->redraw();
}

// callback for generating Data Set for regression
//
void OnGenerateDataSet_Rgr(Fl_Widget *, void *) {
	__trainingDataSize = (S_INT)_dataSetCountSlider->value();
	__regression->_noiseX = (S_INT)_dataSetNoiseXSlider_Rgr->value();
	__regression->_noiseY = (S_INT)_dataSetNoiseYSlider_Rgr->value();
	__regression->GenerateDataSet();
	__mainWindow->redraw();
}



// call back for computing regression
//
void OnComputeRegression(Fl_Widget *, void *) {
	__regression->ComputeRegression();
	__mainWindow->redraw();
}


// callback for generating Data Set for KNN
//
void OnGenerateDataSet_KNN(Fl_Widget *, void *) {
	__trainingDataSize = (S_INT)_dataSetCountSlider->value();
	__KNN->_percent = (S_INT)_dataSetPercent_KNN->value();
	__KNN->_extentionCls1 = (S_INT)_dataSetExtentionCls1_KNN->value();
	__KNN->_extentionCls2 = (S_INT)_dataSetExtentionCls2_KNN->value();
	__KNN->GenerateDataSet();
	__mainWindow->redraw();
}

// callback for inserting random data sample
// not used in UI
//
void OnInsertDataSample_KNN(Fl_Widget *, void *) {
	__KNN->InsertDataSample_KNN();
	__mainWindow->redraw();
}

// callback for computing KNN
//
void OnComputeKNN(Fl_Widget *, void *) {
	__KNN->_sample = (S_INT)_sampleSlider_KNN->value();
	__KNN->ComputeKNN();
	__mainWindow->redraw();
}


// callback for compute perceptron
//
void OnComputePerceprton(Fl_Widget *, void *) {
	//__Perceptron->_threshold = (float)_thresholdSlider_Prp->value();
	__Perceptron->_learningRate = (float)_learningRateSlider_Prp->value();
	__Perceptron->ComputePerceptron();
	__mainWindow->redraw();
}


// callback for clearing screen
//
void OnClearScreen(Fl_Widget *, void *) {
	if (__trainingDataSet) {
		delete __trainingDataSet;
		__trainingDataSet = NULL;
	}
	if (__KNN->_dataSample) {
		delete __KNN->_dataSample;
		__KNN->_dataSample = -NULL;
	}
	if (__Perceptron->_trainingSamples.size()) {
		__Perceptron->_trainingSamples.clear();
		__Perceptron->_weights[0] = __Perceptron->_weights[1] = __Perceptron->_weights[2] = 0.0;
	}
	_graphWindow->redraw();
}


// callback for making sure that the KNN sample number is odd not even
//
void OnSetOddSampleValue(Fl_Widget *w, void *) {
	int val = ((Fl_Value_Slider *)w)->value();
	val = 2 * (val / 2) + 1;
	((Fl_Value_Slider *)w)->value(val);
}

// callback for showing help
//
void OnShowHelp(Fl_Widget *, void *) {
	const char *helpStr = "\
[Training Data Size]\n\
[Training Size] number of training examples to generate\n\n\
[Linear Regression]\n\
[Noise X] noise of trainign examples in x dimension\n\
[Noise Y] noise of training examples in y dimension\n\n\
[KNN Classification]\n\
[Proportion %] proportion percent of training examples class RED to class BLUE\n\
[Area Class 1] rectangle area of training examples class RED\n\
[Area Class 2] rectangle area of training examples class BLUE\n\
[KNN Samples] number of KNN samples, k\n\n\
[Perceprton Classification]\n\
[Learning Rate] rate of updating the waights\n\n\
[KNN -> <middle> mouse click on screen to insert a test example]\n\
[Perceptron -> <left> mouse click on screen to insert training examples class RED]\n\
[Perceptron -> <right> mouse click on screen to insert training examples class BLUE]\n\
";

	Fl_Window *helpWin = new Fl_Window(570, 340, "help");
	Fl_Box *helpBox = new Fl_Box(0, 0, 570, 340, helpStr);
	helpBox->labelcolor(38U);
	helpWin->end();
	helpWin->show();
}

// function to make the main window
//
void MakeMainWindow(const char *) {
	// main window
	//
	__mainWindow = new MainWindow(__Win_W, __Win_H, "Regression / KNN / Perceptron");

	// help Button
	//
	Fl_Button *helpButton = new Fl_Button(__Ctrl_Col + 175, __Ctrl_row - 50, 55, 20, "help");
	helpButton->align(FL_ALIGN_CENTER);
	helpButton->callback(OnShowHelp);

	// training data set count slider
	//
	(new Fl_Box(__Ctrl_Col, __Ctrl_row, 200, 20, "[Training Data Size]"))->labelcolor(38U);	 	__Ctrl_row += __Ctrl_row_delta;
	_dataSetCountSlider = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Training Size");					__Ctrl_row += __Ctrl_row_delta;
	_dataSetCountSlider->bounds(2, 10000);
	_dataSetCountSlider->value(100);
	_dataSetCountSlider->align(FL_ALIGN_LEFT);
	_dataSetCountSlider->type(1);
	_dataSetCountSlider->step(1);

	_clearScreenButton = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Clear Screen");	__Ctrl_row += __Ctrl_row_delta + 20;
	_clearScreenButton->color(46U);
	_clearScreenButton->callback(OnClearScreen);
	// Regression Widgets
	//
	(new Fl_Box(__Ctrl_Col, __Ctrl_row, 200, 20, "[Linear Regression]"))->labelcolor(38U);		__Ctrl_row += __Ctrl_row_delta;
	// data noise X slider
	//
	_dataSetNoiseXSlider_Rgr = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Noise X");	__Ctrl_row += __Ctrl_row_delta;
	_dataSetNoiseXSlider_Rgr->bounds(1, 300);
	_dataSetNoiseXSlider_Rgr->value(50);
	_dataSetNoiseXSlider_Rgr->align(FL_ALIGN_LEFT);
	_dataSetNoiseXSlider_Rgr->type(1);
	// data noise Y slider
	//
	_dataSetNoiseYSlider_Rgr = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Noise Y");	__Ctrl_row += __Ctrl_row_delta;
	_dataSetNoiseYSlider_Rgr->bounds(1, 300);
	_dataSetNoiseYSlider_Rgr->value(50);
	_dataSetNoiseYSlider_Rgr->align(FL_ALIGN_LEFT);
	_dataSetNoiseYSlider_Rgr->type(1);
	// Generate Data Set for Regression button
	//
	_dataSetGenButton_Rgr = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Generate Training Data");	__Ctrl_row += __Ctrl_row_delta;
	_dataSetGenButton_Rgr->color(FL_GREEN);
	_dataSetGenButton_Rgr->callback(OnGenerateDataSet_Rgr);
	// Compute Resgression Button
	//
	_computeRegressionButton = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Compute Regression");	__Ctrl_row += __Ctrl_row_delta + 20;
	_computeRegressionButton->color(FL_RED);
	_computeRegressionButton->callback(OnComputeRegression);


	// KNN Widgets
	//
	(new Fl_Box(__Ctrl_Col, __Ctrl_row, 200, 20, "[KNN Classification]"))->labelcolor(38U);				 					__Ctrl_row += __Ctrl_row_delta;
	// percentage class 1 / class 2 slider
	//
	_dataSetPercent_KNN = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Proportion %");					__Ctrl_row += __Ctrl_row_delta;
	_dataSetPercent_KNN->bounds(0, 100);
	_dataSetPercent_KNN->value(50);
	_dataSetPercent_KNN->align(FL_ALIGN_LEFT);
	_dataSetPercent_KNN->type(1);
	_dataSetPercent_KNN->step(1);
	// Area Class 1 Slider
	//
	_dataSetExtentionCls1_KNN = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Area Class 1");					__Ctrl_row += __Ctrl_row_delta;
	_dataSetExtentionCls1_KNN->bounds(1, __Graph_W);
	_dataSetExtentionCls1_KNN->value(__Graph_W);
	_dataSetExtentionCls1_KNN->align(FL_ALIGN_LEFT);
	_dataSetExtentionCls1_KNN->type(1);
	_dataSetExtentionCls1_KNN->step(1);
	// Area Class 2 Slider
	//
	_dataSetExtentionCls2_KNN = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Area Class 2");					__Ctrl_row += __Ctrl_row_delta;
	_dataSetExtentionCls2_KNN->bounds(1, __Graph_W);
	_dataSetExtentionCls2_KNN->value(__Graph_W);
	_dataSetExtentionCls2_KNN->align(FL_ALIGN_LEFT);
	_dataSetExtentionCls2_KNN->type(1);
	_dataSetExtentionCls2_KNN->step(1);
	// Generate Data Set for KNN button
	//
	_dataSetGenButton_KNN = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Generate Training Data");	__Ctrl_row += __Ctrl_row_delta;
	_dataSetGenButton_KNN->color(FL_GREEN);
	_dataSetGenButton_KNN->callback(OnGenerateDataSet_KNN);

//	_generateDataSample_KNN = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Insert Data Sample");	__Ctrl_row += __Ctrl_row_delta;
//	_generateDataSample_KNN->callback(OnInsertDataSample_KNN);
	// KNN Samples Slider
	//
	_sampleSlider_KNN = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "KNN Samples");				__Ctrl_row += __Ctrl_row_delta;
	_sampleSlider_KNN->range(1, 99);
	_sampleSlider_KNN->value(1);
	_sampleSlider_KNN->align(FL_ALIGN_LEFT);
	_sampleSlider_KNN->type(1);
	_sampleSlider_KNN->step(1);
	_sampleSlider_KNN->callback(OnSetOddSampleValue);
	// compute KNN button
	//
	_computeKNN = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Compute KNN");	__Ctrl_row += __Ctrl_row_delta + 20;
	_computeKNN->color(FL_RED);
	_computeKNN->callback(OnComputeKNN);

	// Perceptron Widgets
	//
	(new Fl_Box(__Ctrl_Col, __Ctrl_row, 200, 20, "[Perceptron Classification]"))->labelcolor(38U);				 					__Ctrl_row += __Ctrl_row_delta;
	// perceptron Threshold slider
	//
	/*
	_thresholdSlider_Prp = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Threshold");				__Ctrl_row += __Ctrl_row_delta;
	_thresholdSlider_Prp->bounds(0.05, 5.0);
	_thresholdSlider_Prp->value(0.5);
	_thresholdSlider_Prp->align(FL_ALIGN_LEFT);
	_thresholdSlider_Prp->type(1);
	_thresholdSlider_Prp->step(0.05);
	*/
	// learning rate slider
	//
	_learningRateSlider_Prp = new Fl_Value_Slider(__Ctrl_Col, __Ctrl_row, 200, 20, "Learning Rate");				__Ctrl_row += __Ctrl_row_delta;
	_learningRateSlider_Prp->bounds(0.05, 10.0);
	_learningRateSlider_Prp->value(0.1);
	_learningRateSlider_Prp->align(FL_ALIGN_LEFT);
	_learningRateSlider_Prp->type(1);
	_learningRateSlider_Prp->step(0.05);
	// compute perceprton button
	//
	_computePerceptronButton = new Fl_Button(__Ctrl_Col, __Ctrl_row, 200, 20, "Compute Perceptron");	__Ctrl_row += __Ctrl_row_delta + 20;
	_computePerceptronButton->color(FL_RED);
	_computePerceptronButton->callback(OnComputePerceprton);

	// canva widget
	//
	_graphWindow = new GraphWindow(__Graph_W0, __Graph_H0, __Graph_W, __Graph_H);
	_graphWindow->color(FL_BLACK);
	_graphWindow->end();
	
	Fl_Box *b1 = new Fl_Box(590, 670, 500, 20, "Regression / Classification\tHadi N. Sarraf\tID: 92212559\thadi.sarraf@@yahoo.com");
	b1->align(FL_ALIGN_LEFT);
	b1->labelcolor(38U);

	__mainWindow->resizable(_graphWindow);
	__mainWindow->end();
}



#endif /*__MAINWINDOW_H__*/