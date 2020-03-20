/////////////////////////////////
//Regression - Classification////
//Regression.H///////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////


#ifndef __REGRESSION_H__
#define __REGRESSION_H__

#include <FL/Fl.H>

#include <ctime>
#include <iostream>
using namespace std;

#include "UIConfig.h"
#include "DataSample.h"


class Regression {
public:
	Regression(int X1 = 0, int X2 = __Graph_W):_X1(X1), _X2(X2) {}
	virtual ~Regression() {}

	// method for generating features
	//
	inline void GenerateDataSet() {
		if (__trainingDataSet) {
			delete[] __trainingDataSet;
			__trainingDataSet = NULL;
		}
		__trainingDataSet = new DataSample[__trainingDataSize];
		srand(clock());
		_X1 = 10000;
		_X2 = -10000;
		float x = (float)__Graph_W / __trainingDataSize;
		float y = (float)__Graph_H / __trainingDataSize;
		for (int i = 0; i < __trainingDataSize; i++) {
			S_INT noiseX = rand() % _noiseX - (_noiseX / 2);
			S_INT noiseY = rand() % _noiseY - (_noiseY / 2);
			__trainingDataSet[i]._x = x * i + noiseX;
			__trainingDataSet[i]._y = (y * i) + noiseY;
			if (__trainingDataSet[i]._x < _X1)
				_X1 = __trainingDataSet[i]._x;
			if (__trainingDataSet[i]._x > _X2)
				_X2 = __trainingDataSet[i]._x;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// Regression Equation(y) = mx + h									//
	// m = (NΣXY - (ΣX)(ΣY)) / (NΣX2 - (ΣX)2)							//
	// h = (ΣY - b(ΣX)) / N												//
	// reference:														//
	// https://www.easycalculation.com/statistics/learn-regression.php  //
	//////////////////////////////////////////////////////////////////////
	// call back for computing regression
	//
	inline void ComputeRegression() {
		if (__trainingDataSet) {
			float X = 0;		// sigam x[i], ΣX
			float Y = 0;		// sigma y[i], ΣY
			float XY = 0;		// sigam x[i]*y[i], ΣXY
			float X2 = 0;		// sigma x[i]*x[i], NΣX2
			int N = __trainingDataSize;		// number of training data set
			for (int i = 0; i < __trainingDataSize; i++) {
				X += __trainingDataSet[i]._x;
				Y += __trainingDataSet[i]._y;
				XY += __trainingDataSet[i]._x * __trainingDataSet[i]._y;
				X2 += __trainingDataSet[i]._x * __trainingDataSet[i]._x;
			}
			_M = (N * XY - X * Y) / (N * X2 - X * X);	// slop, m
			_H = (Y - _M * X) / N;						// intercept, h
		}
	}

	// data members
	//
	S_INT _noiseX;				// noise x
	S_INT _noiseY;				// noise y
	float _H;					// interception
	float _M;					// slope
	int _X1;					// X min
	int _X2;					// X max
} *__regression;		// regression object



#endif /*__REGRESSION_H__*/