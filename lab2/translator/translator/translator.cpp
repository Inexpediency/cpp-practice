#include "stdafx.h"
#include "Translator.h"
#include "input_output_utils.h"

int main(int argc, char * argv[])
{
	CTranslator translator;
	std::ifstream input;
	std::ofstream output;
	if (CheckArgumentCount(argc, argv[0]) ||
		!(OpenFile(input, argv[1])) ||
		!(OpenFile(output, argv[2])))
	{
		return 1;
	}
	translator.FillDictionary(input);
	std::string line;
	std::cin >> line;
	while (line != END_STR)
	{
		std::string translation = translator.GetTranslation(line);
		if (translation != "")
		{
			std::cout << translation << std::endl;
		}
		else
		{
			AskForTranslation(translator, line);
		}
		std::cin >> line;
	}
	DumpTranslator(translator, output);
    return 0;
}