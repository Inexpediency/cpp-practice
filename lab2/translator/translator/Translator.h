#pragma once
#include "stdafx.h"


class CTranslator
{
public:
	void FillDictionary(std::istream & input);
	void AddTranslation(std::string word, std::string translation);
	std::string GetTranslation(std::string word);
	void DumpDictionary(std::ostream & output);
	static const char DELIMETR = '=';
private:
	bool m_modified = false;
	std::map<std::string, std::string> m_dictionary;
};
