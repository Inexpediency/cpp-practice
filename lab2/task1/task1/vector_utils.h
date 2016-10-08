#pragma once
#include "stdafx.h"

typedef std::vector<double> doubleVector;

doubleVector ReadVector(std::istream & input);
void ProcessVector(doubleVector & processingVector);
void PrintSortedVector(std::ostream & output, doubleVector & printingVector);