#include "pch.h"
#include "ClassificationTree.h"



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
	if (calculateDistance(newPoint, actual->point) > 400)
	{
		if (actual->external == NULL)
		{
			actual->external = new obj();
			actual->external->point = newPoint;
			actual->external->group = actual->group+1;
			Groups.push_back(actual->external);
		}
		else
		{
			climbTheTree(newPoint, actual->external);
		}
	}
	else
	{
		if (actual->internal == NULL)
		{
			actual->internal = new obj();
			actual->internal->point = newPoint;
			actual->internal->group = actual->group;
			
		}
		else
		{
			climbTheTree(newPoint, actual->internal);
			//TODO: Check If We Don't Lose Points Here
		}
	}
}


ClassificationTree::~ClassificationTree()
{
}
