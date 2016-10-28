#include "stdafx.h"
#include "../translator/Translator.h"

BOOST_AUTO_TEST_SUITE(Translator)

	BOOST_AUTO_TEST_SUITE(Input_output_dictionary)
		
		CTranslator translator;
		
		BOOST_AUTO_TEST_CASE(Fill_dictionary)
		{
			std::ifstream input("dictionary.txt");
			translator.FillDictionary(input);
			Dictionary filledDictionary = translator.GetDictionary();
			Dictionary correctDictionary;
			correctDictionary["food"] = "еда";
			correctDictionary["еда"] = "food";
			correctDictionary["variables"] = "переменная";
			correctDictionary["переменная"] = "variables";
			correctDictionary["class"] = "класс";
			correctDictionary["класс"] = "class";
			correctDictionary["translator"] = "переводчик";
			correctDictionary["переводчик"] = "translator";
			BOOST_CHECK(correctDictionary == filledDictionary);
		}

		BOOST_AUTO_TEST_CASE(Dump_dictionary)
		{
			Dictionary dumpedDictionary = translator.GetDictionary();
			std::ofstream output("dictinary1.txt");
			translator.DumpDictionary(output);
			output.close();
			std::ifstream dumpedDictionaryFile("dictinary1.txt");
			translator.FillDictionary(dumpedDictionaryFile);
			Dictionary filledDictionary = translator.GetDictionary();
			BOOST_CHECK(filledDictionary == dumpedDictionary);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Edit_dictionary)
		
		CTranslator translator;

		BOOST_AUTO_TEST_CASE(Add_translarion)
		{
			translator.AddTranslation("file", "файл");
			Dictionary correctDictionary;
			correctDictionary["file"] = "файл";
			correctDictionary["файл"] = "file";
			Dictionary filledDictionary = translator.GetDictionary();
			BOOST_CHECK(correctDictionary == filledDictionary);
		}

		BOOST_AUTO_TEST_CASE(Get_translation)
		{
			BOOST_CHECK_EQUAL(translator.GetTranslation("file"), "файл");
		}

	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()