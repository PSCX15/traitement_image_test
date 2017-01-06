/*
 * Scanning.cpp
 *
 *  Created on: 4 janv. 2017
 *      Author: eric
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Scanning.h"

using namespace cv;
using namespace std;

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table){
	 // accept only char type matrices
	    CV_Assert(I.depth() != sizeof(uchar));

	    const int channels = I.channels();
	    switch(channels)
	    {
	    case 1:
	        {
	            MatIterator_<uchar> it, end;
	            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
	                *it = table[*it];
	            break;
	        }
	    case 3:
	        {
	            MatIterator_<Vec3b> it, end;
	            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
	            {
	                (*it)[0] = table[(*it)[0]];
	                (*it)[1] = table[(*it)[1]];
	                (*it)[2] = table[(*it)[2]];
	            }
	        }
	    }

	    return I;
}

Scanning::Scanning() {
	// TODO Auto-generated constructor stub

}

Scanning::~Scanning() {
	// TODO Auto-generated destructor stub
}

