#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

struct obj {
	Point point;
	obj* internal;
	obj* external;
	int group;
};

class ClassificationTree
{
public:
	vector <obj*> Groups;
	obj* start;

	ClassificationTree();
	void AddPoint(Point newPoint);
	int calculateDistance(Point x, Point y);
	void climbTheTree(Point newPoint, obj* actual);
	int getGroupsSize();
	vector <Point> getPointsFromGroupById(int id);

	~ClassificationTree();
};

