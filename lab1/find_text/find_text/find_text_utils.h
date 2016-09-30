#pragma once
#include "stdafx.h"

using findStringCallback = std::function<void(int lineIndex, const std::string & line)>;

bool ProcesFileErrors(int namesCount, std::ifstream & input, char * fileNames[]);
bool FindStringInFile(std::ifstream & input, const std::string & comparedString, const findStringCallback & callback);
bool FindStringInFile(std::ifstream & input, const std::string & comparedString);