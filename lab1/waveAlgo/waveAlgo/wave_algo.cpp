#include "stdafx.h"
#include "wave_algo_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream input;
	ofstream output;
	point startPoint, endPoint;
	labyrinth map;
	if (!ProcesFileErrors(argc, input, output, argv))
	{
		return 1;
	}
	if (!ReadLabyrint(input, map, startPoint, endPoint))
	{
		cout << "You do not init start or end point" << endl;
		cout << "Init start point like '" << START_CHAR << "'";
		cout << " and ";
		cout << "end point like '" << END_CHAR << "'" << endl;
		return 1;
	}
	if (!FillLabyrinth(map, startPoint, endPoint))
	{
		cout << "Way is not found. Check labyrinth." << endl;
		return 1;
	}
	FillWay(map, endPoint);
	PrintWay(output, map, startPoint, endPoint);
	return 0;
}