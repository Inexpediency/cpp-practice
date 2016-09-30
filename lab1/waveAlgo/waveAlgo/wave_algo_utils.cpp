#include "stdafx.h"
#include "wave_algo_utils.h"
using namespace std;

bool ProcesFileErrors(int namesCount, ifstream & input, ofstream & output, char * fileNames[])
{
	if (namesCount != 3)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	input.open(fileNames[1]);
	if (!input.is_open())
	{
		cout << "Can not open input file" << endl;
		return false;
	}
	output.open(fileNames[2]);
	if (!output.is_open())
	{
		cout << "Can not open output file" << endl;
		return false;
	}
	return true;
}

bool ReadLabyrint(ifstream & input, labyrinth & map, point & startPoint, point & endPoint)
{
	string line;
	startPoint.level = -1;
	endPoint.level = -1;
	for (int i = 0; getline(input, line); ++i)
	{
		map.push_back(vector<int>());
		for (int j = 0; j < line.length(); ++j)
		{
			if (line[j] == END_CHAR)
			{
				endPoint.x = j;
				endPoint.y = i;
				endPoint.level = 0;
			}
			if (line[j] == START_CHAR)
			{
				startPoint.x = j;
				startPoint.y = j;
				startPoint.level = 0;
				map[i].push_back(-3);
			}
			else 
				map[i].push_back((line[j] == WALL_CHAR) * (-1));
		}
	}
	return startPoint.level >= 0 && endPoint.level >= 0;
}

bool FillLabyrinth(labyrinth & map, const point & startPoint, const point & endPoint)
{
	point currentPoint = startPoint;
	queue<point> points;
	points.push(startPoint);
	do
	{
		currentPoint = points.front();
		points.pop();
		PushPoints(map, currentPoint, points);
	} while (!points.empty() && !((currentPoint.x == endPoint.x) && (currentPoint.y == endPoint.y)));
	return (currentPoint.x == endPoint.x) && (currentPoint.y == endPoint.y);
}

void PushPoints(labyrinth & map, point & currentPoint, queue<point> & points)
{
	currentPoint.level++;
	if (currentPoint.y - 1 >= 0 && currentPoint.y + 1 < map.size())
	{
		currentPoint.y--;
		PushPoint(map, currentPoint, points);
		currentPoint.y += 2;
		PushPoint(map, currentPoint, points);
		currentPoint.y--;
	}
	if (currentPoint.x - 1 >= 0 && currentPoint.x + 1 < map[currentPoint.y].size())
	{
		currentPoint.x--;
		PushPoint(map, currentPoint, points);
		currentPoint.x += 2;
		PushPoint(map, currentPoint, points);
		currentPoint.x--;
	}
	currentPoint.level--;
}

void PushPoint(labyrinth & map, const point & currentPoint, queue<point> & points)
{
	if (!map[currentPoint.y][currentPoint.x])
	{
		points.push(currentPoint);
		map[currentPoint.y][currentPoint.x] = currentPoint.level;
	}
}

void FillWay(labyrinth & map, const point & endPoint)
{
	point currentPoint = endPoint;
	while (map[currentPoint.y][currentPoint.x] != (-3))
	{
		map[currentPoint.y][currentPoint.x] = (-2);
		currentPoint = GetVicinityMinPoint(map, currentPoint);
	}
}

point & GetVicinityMinPoint(const labyrinth & map, point currentPoint)
{
	point minPoint = currentPoint;
	if (currentPoint.y - 1 >= 0 &&
		(map[currentPoint.y - 1][currentPoint.x] >= 0 || map[currentPoint.y - 1][currentPoint.x] == (-3)))
	{
		minPoint.x = currentPoint.x;
		minPoint.y = currentPoint.y - 1;
	}
	if (currentPoint.y + 1 < map.size() &&
		(map[currentPoint.y + 1][currentPoint.x] >= 0 || map[currentPoint.y + 1][currentPoint.x] == (-3)) && 
        (minPoint.x == currentPoint.x && minPoint.y == currentPoint.y || map[currentPoint.y + 1][currentPoint.x] < minPoint.level))
	{
		minPoint.x = currentPoint.x;
		minPoint.y = currentPoint.y + 1;
	}
	if (currentPoint.x - 1 >= 0 &&
		(map[currentPoint.y][currentPoint.x - 1] >= 0 || map[currentPoint.y][currentPoint.x - 1] == (-3)) &&
		(minPoint.x == currentPoint.x && minPoint.y == currentPoint.y || map[currentPoint.y][currentPoint.x - 1] < minPoint.level))
	{
		minPoint.x = currentPoint.x - 1;
		minPoint.y = currentPoint.y;
	}
	if (currentPoint.x + 1 < map[currentPoint.y].size() &&
		(map[currentPoint.y][currentPoint.x + 1] >= 0 || map[currentPoint.y][currentPoint.x + 1] == (-3)) &&
		(minPoint.x == currentPoint.x && minPoint.y == currentPoint.y || map[currentPoint.y][currentPoint.x + 1] < minPoint.level))
	{
		minPoint.x = currentPoint.x + 1;
		minPoint.y = currentPoint.y;
	}
	minPoint.level = map[minPoint.y][minPoint.x];
	return minPoint;
}

void PrintWay(ofstream & output, const labyrinth & map, point & startPoint, point & endPoint)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			if (j == startPoint.x && i == startPoint.y)
				output << START_CHAR;
			else if (j == endPoint.x && i == endPoint.y)
				output << END_CHAR;
			else
				switch (map[i][j])
				{
					case (-1):
						output << WALL_CHAR;
						break;
					case (-2):
						output << WAY_CHAR;
						break;
					default:
						output << ' ';
						break;
				}
		}
		output << endl;
	}
}