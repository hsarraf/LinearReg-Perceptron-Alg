/////////////////////////////////
//Regression - Classification////
//Perceptron.H///////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////


#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include <FL/Fl.H>

#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

#include "UIConfig.h"
#include "DataSample.h"


class Perceptron {
public:
	Perceptron() { _weights[0] = _weights[1] = _weights[2] = 0.0; }
	virtual ~Perceptron() {}

	// method for computing perceptron
	//
	inline void ComputePerceptron() {
		_weights[0] = _weights[1] = _weights[2] = 0.0;
		int y, Y, err, errCount;
		while (true) {
			errCount = 0;	// count errors on all samples
			for (int i = 0; i < _trainingSamples.size(); i++) {
				// y is the dot product (W.X)
				// W = _weights, X = (_trainingSamples[i]._x, _trainingSamples[i]._y)
				//
				y = _weights[1] * _trainingSamples[i]._x + _weights[2] * _trainingSamples[i]._y + _weights[0];
				// Y is perceptron output
				// (y >= 0) => Y = 1, otherwise Y = 0
				//
				Y = y >= 0 /*_threshold*/;
				// compute error of perceptron and actual results
				//
				err = _trainingSamples[i]._id - Y;
				// update wights
				//
				if (err != 0) {
					errCount++;
					_weights[0] += _learningRate * err;									// w[0] is the bias, b
					_weights[1] += _learningRate * err * _trainingSamples[i]._x;
					_weights[2] += _learningRate * err * _trainingSamples[i]._y;
				}
			}
			// checks if all weights are truly set for all samples
			// if true so there is no need to iterate anymore
			//
			if (errCount == 0)
				break;
		}
	}

	// data members
	//
	vector<DataSample> _trainingSamples;	// training examples
	float _threshold;		// threshold, landa
	float _learningRate;	// learning rate
	float _weights[3];		// weights list
} *__Perceptron;	// perceptron object


#endif /*__PERCEPTRON_H__*/