#include "stdafx.h"
#include "Translator.h"

void CTranslator::FillDictionary(std::istream & input)
{
	std::string line;
	m_modified = true;
	while (std::getline(input, line))
	{
		size_t delimetrPos = line.find(CTranslator::DELIMETR);
		std::string word = line.substr(delimetrPos);
		std::string tranlation = line.substr(delimetrPos + 1, line.size() - delimetrPos);
		m_dictionary[word] = tranlation;
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
}

void CTranslator::AddTranslation(std::string word, std::string translation)
{
	m_dictionary[ToLowCase(word)] = ToLowCase(translation);
}


std::string CTranslator::GetTranslation(std::string word)
{
	auto it = m_dictionary.find(word);
	return it == m_dictionary.end() ? "" : it->second;
}

void CTranslator::DumpDictionary(std::ostream & output)
{
	for (auto it = m_dictionary.begin(); it != m_dictionary.end(); ++it)
	{
		output << it->first << "=" << it->second << std::endl;
	}
}