#include "stdafx.h"
#include "Translator.h"

void CTranslator::FillDictionary(std::istream & input)
{
	std::string line;
	m_modified = true;
	while (std::getline(input, line))
	{
		std::size_t delimetrPos = line.find(CTranslator::DELIMETR);
		std::string word = line.substr(0, delimetrPos);
		std::string tranlation = line.substr(delimetrPos + 1, line.size() - delimetrPos);
		AddTranslation(word, tranlation);	
		m_modified = false;
	}
}

std::string ToLowCase(std::string str)
{
	std::locale loc;
	for (auto & ch : str)
	{
		ch = std::tolower(ch, loc);
	}
	return str;
}

bool CTranslator::IsModified() const
{
	return m_modified;
}

void CTranslator::AddTranslation(const std::string word, const std::string translation)
{
	m_dictionary[ToLowCase(word)] = ToLowCase(translation);
	m_modified = true;
}


std::string CTranslator::GetTranslation(const std::string word) const
{
	auto it = m_dictionary.find(ToLowCase(word));
	return it == m_dictionary.end() ? "" : it->second;
}

void CTranslator::DumpDictionary(std::ostream & output) const
{
	for (auto it = m_dictionary.begin(); it != m_dictionary.end(); ++it)
	{
		output << it->first << CTranslator::DELIMETR << it->second << std::endl;
	}
}


std::map<std::string, std::string> CTranslator::GetDictionary()
{
	std::map<std::string, std::string> dictionary;
	for (auto it = m_dictionary.begin(); it != m_dictionary.end(); ++it)
	{
		dictionary[it->first] = it->second;
	}
	return move(dictionary);
}