#pragma once
#include "stdafx.h"

using labyrinth = std::vector<std::vector<int>>;
struct point
{
	unsigned char x;
	unsigned char y;
	unsigned char level;
};
const char WALL_CHAR = '#';
const char START_CHAR = 'A';
const char WAY_CHAR = '*';
const char END_CHAR= 'B';

bool ProcesFileErrors(int namesCount, std::ifstream & input, std::ofstream & output, char * fileNames[]);
bool ReadLabyrint(std::ifstream & input, labyrinth & map, point & startPoint, point & endPoint);
bool FillLabyrinth(labyrinth & map, const point & startPoint, const point & endPoint);
void PushPoints(labyrinth & map, point & currentPoint, std::queue<point> & points);
void PushPoint(labyrinth & map, const point & currentPoint, std::queue<point> & points);
void FillWay(labyrinth & map, const point & endPoint);
point & GetVicinityMinPoint(const labyrinth & map, point currentPoint);
void PrintWay(std::ofstream & output, const labyrinth & map, point & startPoint, point & endPoint);