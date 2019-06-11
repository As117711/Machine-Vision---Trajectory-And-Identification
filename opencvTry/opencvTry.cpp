// opencvTry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ClassificationTree.h"
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
	vector <vector<Point>> vectors;
	vector <int> valuableVectors;
	vector<Point> contours_poly;
	Rect boundRect;
	

	Mat previousFrame, frame, finalFrame, result1, result2, result3;
	sourceMovie >> previousFrame;
	finalFrame = previousFrame.clone();
	cvtColor(previousFrame, previousFrame, COLOR_BGR2GRAY);
	
	
	while (1)
	{
		if (!sourceMovie.read(frame)) { break; }

		sourceMovie >> frame;

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		absdiff(frame, previousFrame, result1);
		getSomeFunWithTreshold(result1, 20);

		erode(result1, result1, getStructuringElement(MORPH_RECT, Size(4, 4)));
		dilate(result1, result1, getStructuringElement(MORPH_RECT, Size(2, 2)));


		findContours(result1, vectors, RETR_LIST, CHAIN_APPROX_SIMPLE);

		ClassificationTree* Tree = new ClassificationTree();

		vector<Point*> previousPoint;
		Point* actualPoint;

		for (int i = 0; i < vectors.size(); i++)
		{
			if (contourArea(vectors[i]) > 200) {
				//drawContours(finalFrame, vectors, i, Scalar(255, 0, 0), 2); Contours 
				valuableVectors.push_back(i);

				approxPolyDP(Mat(vectors[i]), contours_poly, 3, true);
				boundRect = boundingRect(Mat(contours_poly));

				cout << "S: " << contours_poly.size() << " :S";

				Moments mu = moments(vectors[i], false);
				Point pos = Point(mu.m10 / mu.m00, mu.m01 / mu.m00);
				/*rectangle(finalFrame, boundRect.tl(), boundRect.br(), Scalar(125, 250, 125), 2, 8, 0);
				line(finalFrame, boundRect.tl(), boundRect.br(), Scalar(250, 125, 125), 2, 8, 0);
				line(finalFrame, Point(boundRect.x + boundRect.width, boundRect.y), Point(boundRect.x, boundRect.y + boundRect.height), Scalar(250, 125, 125), 2, 8, 0);
				*/
				circle(finalFrame, Point(boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2), 3, Scalar(250, 255, 125), 3);
				//circle(finalFrame, pos, 3, Scalar(250, 255, 125), 5);
				actualPoint = new Point(boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
				int check = Tree->getGroupsSize();
				int groupDestination = Tree->AddPoint(Point(boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2));
				if (!previousPoint.empty())
				{
					line(finalFrame, *previousPoint[groupDestination], *actualPoint,Scalar(255,255,255),3);
				}
				cout << "\nCheck : " << check << " groupDestination: " << groupDestination << "\n";
				if (check > groupDestination || previousPoint.empty())
				{
					cout << "Yeah!";
					previousPoint.push_back(actualPoint);
				}
				else
				{
					cout << "NOT"; //Here it is.
					if (previousPoint.empty()) { previousPoint.push_back(actualPoint); }
					else { previousPoint[groupDestination - 1] = actualPoint; }

				}
				
				//imshow("finalFrame", finalFrame);
				waitKey(0);

			}
		}

		int counter = Tree->getGroupsSize();
		for (int i = 0; i < counter; i++)
		{
			vector <Point> actual = Tree->getPointsFromGroupById(i),test;
			approxPolyDP(Mat(actual), test, 3, true);
			boundRect = boundingRect(Mat(test));
			circle(finalFrame, Point(boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2), 3+i, Scalar(250, 125, 125), 3);
			
			imshow("finalFrame", finalFrame);
			
		}

		//imshow("result1",result1);
		//imshow("frame", frame); 
		//imshow("finalFrame", finalFrame);
		
		waitKey(0);
		previousFrame = frame.clone();
	}

	for (int i = 0; i < valuableVectors.size(); i++)
	{
		cout << " " << valuableVectors[i];
	}
	waitKey(0);
	return 0;
}
