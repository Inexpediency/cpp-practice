#pragma once
#include "stdafx.h"


bool CheckReplacingString(const std::string & str);
bool CheckArgumentCount(int argumentCount);
std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace);