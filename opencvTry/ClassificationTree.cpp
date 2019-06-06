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
	if (calculateDistance(newPoint, actual->point) > 200)
	{
		if (actual->external == NULL)
		{
			actual->external = new obj();
			actual->external->point = newPoint;
			actual->external->group = actual->group+1;
			Groups.push_back(actual->external);
			cout << "\nNew External Added: " << newPoint << " Group: " << actual->external->group << " \n";
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
			cout << "\nNew Internal Added: " << newPoint << " Group: " << actual->internal->group << " \n";
		}
		else
		{
			climbTheTree(newPoint, actual->internal);
			//TODO: Check If We Don't Lose Points Here
		}
	}
}

int ClassificationTree::getGroupsSize()
{
	return Groups.size();
}

vector<Point> ClassificationTree::getPointsFromGroupById(int id)
{
	vector <Point> tmp;
	obj* actual = Groups[id];
	tmp.push_back(actual->point);
	while (actual->internal != NULL)
	{
		actual = actual->internal;
		tmp.push_back(actual->point);
		//TODO Check If We Do Not Lose The Last One Or Externals
	}
	
	return tmp;
}


ClassificationTree::~ClassificationTree()
{
}
