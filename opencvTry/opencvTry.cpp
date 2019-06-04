// opencvTry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int bins = 1;
/// Function Headers
void median(int, void*);

VideoCapture getMyMovie(string path)
{
	VideoCapture sourceMovie(path);
	if (sourceMovie.isOpened() == false) {
		cout << "Your movie source cannot be opened.";
	}
	
	return sourceMovie;
}

void getSomeFunWithTreshold(Mat& current, int val)
{
	threshold(current, current, val, 255, THRESH_BINARY);
}


int main()
{
	VideoCapture sourceMovie = getMyMovie("movies/AnotherTriple.mp4");
	vector <vector<Point>> vectors, hit;
	

	Mat previousFrame, frame, finalFrame, result1, result2, result3;
	sourceMovie >> previousFrame;
	finalFrame = previousFrame.clone();
	cvtColor(previousFrame, previousFrame, COLOR_BGR2GRAY);
	
	
	while(1)
	{
		if (!sourceMovie.read(frame)) { break; }

		sourceMovie >> frame;
		
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		absdiff(frame, previousFrame, result1);
		getSomeFunWithTreshold(result1, 20);
		
		erode(result1, result1, getStructuringElement(MORPH_RECT,Size(4,4)));
		dilate(result1, result1, getStructuringElement(MORPH_RECT,Size(2,2)));
		

		findContours(result1, vectors, RETR_LIST, CHAIN_APPROX_SIMPLE);
		for (int i = 0; i < vectors.size(); i++)
		{
			if (contourArea(vectors[i]) > 200) {
				drawContours(finalFrame, vectors, i, Scalar(255, 0, 0), 2);
			}
		}

		imshow("result1",result1);
		imshow("frame", frame); 
		imshow("finalFrame", finalFrame);
		
		waitKey(0);
		previousFrame = frame.clone();
	}
	return 0;
}
