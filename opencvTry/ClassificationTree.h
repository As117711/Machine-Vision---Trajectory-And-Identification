#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class ClassificationTree
{
public:
	vector <obj*> Groups;
	obj* start;

	ClassificationTree();
	void AddPoint(Point newPoint);
	int calculateDistance(Point x, Point y);
	void climbTheTree(Point newPoint, obj* actual);
	~ClassificationTree();
};

