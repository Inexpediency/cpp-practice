#pragma once
#include <string>
#include <map>
#include <iostream>

typedef std::map<std::string, std::string> Dictionary;

class CTranslator
{
public:
	bool IsModified() const;
	void FillDictionary(std::istream & input);
	void AddTranslation(const std::string word, const std::string translation);
	Dictionary GetDictionary();
	std::string GetTranslation(const std::string word) const;
	void DumpDictionary(std::ostream & output) const;
private:
	bool m_modified = false;
	Dictionary m_dictionary;
};
