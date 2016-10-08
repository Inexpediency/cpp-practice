#pragma once
#include "stdafx.h"
#include "Translator.h"

const std::string END_STR = "...";
const std::string AGREE_STATMENT = "Yes";
const std::string DISAGREE_STATMENT = "NO";

bool OpenFile(std::ofstream & output, std::string fileName);
bool OpenFile(std::ifstream & output, std::string fileName);
bool CheckArgumentCount(int argumentCount, std::string programName);
void AskForTranslation(CTranslator & translator, const std::string & word);
void DumpTranslator(const CTranslator & translator, std::ofstream & output);