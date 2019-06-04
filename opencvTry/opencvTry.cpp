// opencvTry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

VideoCapture getMyMovie(string path)
{
	VideoCapture sourceMovie(path);
	if (sourceMovie.isOpened() == false) {
		cout << "Your movie source cannot be opened.";
	}
	
	return sourceMovie;
}


int main()
{
	VideoCapture sourceMovie = getMyMovie("movies/AnotherTriple.mp4");

	Mat previousFrame, frame, nextFrame, result1, result2, result3;
	sourceMovie >> previousFrame;
	cvtColor(previousFrame, previousFrame, COLOR_BGR2GRAY);

	while(1)
	{
		if (!sourceMovie.read(frame)) { break; }

		sourceMovie >> frame;
		
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		erode(frame, frame, Mat());
		erode(previousFrame, previousFrame, Mat());

		absdiff(frame, previousFrame, result1);
		threshold(result1, result1, 20, 255, THRESH_BINARY);
		erode(result1, result1, Mat());
		morphologyEx(result1, result1, MORPH_OPEN, Mat());
		

		imshow("result1",result1);
		imshow("frame", frame);
		waitKey(0);
		previousFrame = frame.clone();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
