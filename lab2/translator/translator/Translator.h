#pragma once
#include "stdafx.h"


class CTranslator
{
public:
	bool IsModigied() const;
	void FillDictionary(std::istream & input);
	void AddTranslation(const std::string word, const std::string translation);
	std::string GetTranslation(const std::string word) const;
	void DumpDictionary(std::ostream & output) const;
	static const char DELIMETR = '=';
private:
	bool m_modified = false;
	std::map<std::string, std::string> m_dictionary;
};
