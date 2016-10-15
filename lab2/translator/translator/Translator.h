#pragma once
#include "stdafx.h"


class CTranslator
{
public:
	bool IsModified() const;
	void FillDictionary(std::istream & input);
	void AddTranslation(const std::string word, const std::string translation);
	std::map<std::string, std::string> GetDictionary();
	std::string GetTranslation(const std::string word) const;
	void DumpDictionary(std::ostream & output) const;
private:
	bool m_modified = false;
	std::map<std::string, std::string> m_dictionary;
};
