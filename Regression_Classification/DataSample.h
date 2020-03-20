/////////////////////////////////
//Regression - Classification////
//DataSample.H///////////////////
//[Author] Hadi N. Sarraf////////
//[ID] 92212559//////////////////
//[Mail] hadi.sarraf@yahoo.com///
//[Date] 5/22/2015///////////////
/////////////////////////////////


#ifndef __DATASAMPLE_H__
#define __DATASAMPLE_H__

// S_INT short int
//
typedef short int S_INT;
// class data sample metric 2d
//
class DataSample {
public:
	DataSample(int id = -1, Fl_Color clr = FL_GREEN) : _id(id), _clr(clr){}
	DataSample(int x, int y, int id = -1, Fl_Color clr = FL_GREEN) : _id(id), _x(x), _y(y), _clr(clr) {};
	S_INT _id;				// sample Id
	S_INT _x;				// x position
	S_INT _y;				// y position
	Fl_Color _clr;			// sample color
	S_INT _dist;			// distance
} *__trainingDataSet;	// trainig data set / data sample
int __trainingDataSize;		// training data size


#endif /*__DATASAMPLE_H__*/