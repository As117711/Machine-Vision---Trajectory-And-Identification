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
	int groupCounter = 0;

	ClassificationTree(); //Vector last points w konstruktorze? I odleg³oœci¹
	//sprawdzaæ poprzednie grupy i ³¹czyæ liniê trajektori¹?
	int AddPoint(Point newPoint);
	int calculateDistance(Point x, Point y);
	int climbTheTree(Point newPoint, obj* actual);
	int getGroupsSize();
	vector <Point> getPointsFromGroupById(int id);

	void ClearMyPoints(obj * current);

	~ClassificationTree();
};

