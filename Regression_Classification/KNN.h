/////////////////////////////////
//Regression - Classification////
//KNN.H//////////////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////



#ifndef __KNN_H__
#define __KNN_H__

#include <FL/Fl.H>

#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

#include "UIConfig.h"
#include "DataSample.h"


// bubble sort//////////////////////////
inline void swap(DataSample *s1, DataSample *s2) {
	DataSample t = *s1;
	*s1 = *s2;
	*s2 = t;
}
void BubbleSort(DataSample *S, unsigned n, unsigned k) {
	bool sorted = false;
	for (unsigned i = 0; i < k && !sorted; i++) {
		sorted = true;
		for (unsigned j = 0; j < n - i - 1; j++) {
			if (S[j]._dist < S[j + 1]._dist) {
				swap(&S[j], &S[j + 1]);
				sorted = false;
			}
		}
	}
}


// KNN Class ///////////////////
class KNN {
public:
	KNN(){ _dataSample = new DataSample; }
	virtual ~KNN() {
		if (_dataSample) { delete _dataSample; _dataSample = NULL; }
	}

	// method for generating features
	//
	inline void GenerateDataSet() {
		// training data allocation
		//
		if (__trainingDataSet) {
			delete[] __trainingDataSet;
			__trainingDataSet = NULL;
		}
		__trainingDataSet = new DataSample[__trainingDataSize];
		srand(clock());		// change seed, clock milliseconds
		// set the percentage of classes
		//
		int p = (int)(__trainingDataSize * _percent / 100);
		// generate data set
		// class 1
		//
		for (int i = 0; i < p; i++) {
			__trainingDataSet[i]._id = 0;
			__trainingDataSet[i]._x = rand() % _extentionCls1;
			__trainingDataSet[i]._y = rand() % _extentionCls1 * __Graph_H / __Graph_W;
			__trainingDataSet[i]._clr = FL_RED;		// set color to red for class 2
		}
		// class 2
		//
		for (int i = p; i < __trainingDataSize; i++) {
			__trainingDataSet[i]._id = 1;
			__trainingDataSet[i]._x = rand() % _extentionCls2;
			__trainingDataSet[i]._y = rand() % _extentionCls2 * __Graph_H / __Graph_W;
			__trainingDataSet[i]._clr = FL_BLUE;		// set color to blue for class 2
		}
	}

	// method for generating random sample data
	// not used in UI
	//
	inline void InsertDataSample_KNN() {
		srand(clock());
		if (_dataSample) {
			delete _dataSample;
			_dataSample = NULL;
		}
		_dataSample = new DataSample();
		_dataSample->_x = rand() % __Graph_W;
		_dataSample->_y = rand() % __Graph_H;
		_dataSample->_id = rand() % 2;
	}

	// method for insetring sample dta by clicking
	//
	inline void InsertDataSample_KNN(int x, int y) {
		srand(clock());
		if (_dataSample) {
			delete _dataSample;
			_dataSample = NULL;
		}
		_dataSample = new DataSample();
		_dataSample->_x = x;
		_dataSample->_y = y;
		_dataSample->_id = rand() % 2;
	}

	// compute KNN /////////////////
	inline void ComputeKNN() {
		// check if data is set
		//
		if (!__trainingDataSet || !_dataSample)
			return;
		// check if data are generated for KNN not for regression
		//
		if (__trainingDataSet[0]._id == -1)
			return;
		// compute the distance between sample data and all training data
		//
		for (int i = 0; i < __trainingDataSize; i++)
			__trainingDataSet[i]._dist = sqrt(pow(__trainingDataSet[i]._x - _dataSample->_x, 2) + pow(__trainingDataSet[i]._y - _dataSample->_y, 2));
		// sort the training data based on distances using bubble sort
		//
		BubbleSort(__trainingDataSet, __trainingDataSize, _sample);
		// 
		int cls1Count = 0; // number of samples of class 1
		int cls2Count = 0; // number of samples of class 2
		// count the number of samples in each class
		//
		for (int i = __trainingDataSize - 1; i >= __trainingDataSize - _sample; i--) {
			if (__trainingDataSet[i]._id == 0)
				cls1Count++;
			else if (__trainingDataSet[i]._id == 1)
				cls2Count++;
		}
		// set the id and color of the sample data based on the vote
		//
		_dataSample->_id = cls1Count > cls2Count ? 0 : 1;
		_dataSample->_clr = cls1Count > cls2Count ? FL_RED : FL_BLUE;
	}

	// data memebers
	//
	S_INT _percent;			// percentage of class1 / class2
	S_INT _extentionCls1;	// rectangle area of class 1
	S_INT _extentionCls2;	// rectangle area of class 2
	S_INT _sample;			// number of KNN samples
	DataSample *_dataSample;
} *__KNN;	// KNN object



#endif /*__KNN_H__*/
