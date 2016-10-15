#include "stdafx.h"
#include "../translator/Translator.h"

BOOST_AUTO_TEST_SUITE(Translator)

	BOOST_AUTO_TEST_SUITE(Input_output_dictionary)
		
		CTranslator translator;
		
		BOOST_AUTO_TEST_CASE(Fill_dictionary)
		{
			std::ifstream input("dictionary.txt");
			translator.FillDictionary(input);
			std::map<std::string, std::string> filledDictionary = translator.GetDictionary();
			std::map<std::string, std::string> correctDictionary;
			correctDictionary["food"] = "���";
			correctDictionary["variables"] = "����������";
			correctDictionary["class"] = "�����";
			correctDictionary["translator"] = "����������";
			BOOST_CHECK(correctDictionary == filledDictionary);
		}

		BOOST_AUTO_TEST_CASE(Dump_dictionary)
		{
			std::map<std::string, std::string> dumpedDictionary = translator.GetDictionary();
			std::ofstream output("dictinary1.txt");
			translator.DumpDictionary(output);
			output.close();
			std::ifstream dumpedDictionaryFile("dictinary1.txt");
			translator.FillDictionary(dumpedDictionaryFile);
			std::map<std::string, std::string> filledDictionary = translator.GetDictionary();
			BOOST_CHECK(filledDictionary == dumpedDictionary);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Edit_dictionary)
		
		CTranslator translator;

		BOOST_AUTO_TEST_CASE(Add_translarion)
		{
			translator.AddTranslation("file", "����");
			std::map<std::string, std::string> correctDictionary;
			correctDictionary["file"] = "����";
			std::map<std::string, std::string> filledDictionary = translator.GetDictionary();
			BOOST_CHECK(correctDictionary == filledDictionary);
		}

		BOOST_AUTO_TEST_CASE(Get_translation)
		{
			BOOST_CHECK_EQUAL(translator.GetTranslation("file"), "����");
		}

	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()