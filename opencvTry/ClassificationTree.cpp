#include "pch.h"
#include "ClassificationTree.h"

struct obj {
	Point point;
	obj* internal;
	obj* external;
	int group;
};


ClassificationTree::ClassificationTree()
{
}

void ClassificationTree::AddPoint(Point newPoint)
{
	if (start == NULL)
	{ 
		start = new obj();
		start->point = newPoint;
		start->group = 1;
		Groups.push_back(start);
	}
	else
	{
		climbTheTree(newPoint, start);
	}
}

int ClassificationTree::calculateDistance(Point x, Point y)
{
	return sqrt((y.y-x.y)^2+(y.x-x.x)^2);
}

void ClassificationTree::climbTheTree(Point newPoint, obj * actual)
{
	if (calculateDistance(newPoint, start->point) > 400)
	{

	}
	else
	{

	}
}


ClassificationTree::~ClassificationTree()
{
}
