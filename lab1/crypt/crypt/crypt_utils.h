#pragma once
#include "stdafx.h"

const std::string CRYPT_PREFIX = "crypt";
const std::string deCRYPT_PREFIX = "decrypt";

bool ProcesFileErrors(std::ifstream & input, std::ofstream & output, int namesCount, char * fileNames[]);
void Cript(std::ifstream & input, std::ofstream & output, char key);
void Decript(std::ifstream & input, std::ofstream & output, char key);
