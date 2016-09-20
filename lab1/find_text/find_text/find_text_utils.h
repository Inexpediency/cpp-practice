#pragma once
#include "stdafx.h"

bool procesFileErrors(int namesCount, std::ifstream & input, char * fileNames[]);
int printStringPos(std::ifstream & input, std::string comparedString);