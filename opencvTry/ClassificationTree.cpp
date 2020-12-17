#include "pch.h"
#include "ClassificationTree.h"



ClassificationTree::ClassificationTree()
{
}

int ClassificationTree::AddPoint(Point newPoint)
{
	if (start == NULL)
	{ 
		start = new obj();
		start->point = newPoint;
		start->group = 1;
		Groups.push_back(start);
		groupCounter++;
		return 1;
	}
	else
	{
		int result = climbTheTree(newPoint, start);
		return result;
	}
}

int ClassificationTree::calculateDistance(Point x, Point y)
{
	return sqrt((y.y-x.y)^2+(y.x-x.x)^2);
}

int ClassificationTree::climbTheTree(Point newPoint, obj * actual)
{
	int distance = calculateDistance(newPoint, actual->point);
	cout <<"\nDistance: "<<distance<<"\n";
	if (distance > 10 || distance<-1000000)
	{
		if (actual->external == NULL)
		{
			actual->external = new obj();
			actual->external->point = newPoint;
			actual->external->group = actual->group+1;
			Groups.push_back(actual->external);
			cout << "\nNew External Added: " << newPoint << " Group: " << actual->external->group << " \n";
			groupCounter++;
			return actual->group + 1;
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
			return actual->group;
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
	return groupCounter;
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

void ClassificationTree::ClearMyPoints(obj* current)
{
	ClearMyPoints(current->external);
	ClearMyPoints(current->internal);
	delete current;
}

ClassificationTree::~ClassificationTree()
{
}
