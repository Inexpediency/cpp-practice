#include "stdafx.h"
#include "../MyList/MyList.h"

struct MyListFixture
{
	CMyList<std::string> stringList = CMyList<std::string>();
	CMyList<int> intList = CMyList<int>();
};
BOOST_FIXTURE_TEST_SUITE(CMyList_on_create, MyListFixture)
	BOOST_AUTO_TEST_CASE(empty)
	{
		BOOST_CHECK(stringList.IsEmpty());
		BOOST_CHECK(intList.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(have_zero_length)
	{
		BOOST_CHECK_EQUAL(stringList.GetSize(), 0);
		BOOST_CHECK_EQUAL(intList.GetSize(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_be_append_at_end_by_string)
	{
		stringList.PushBack("Some string");
		BOOST_CHECK_EQUAL(stringList.GetLastElement(), "Some string");
		BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "Some string");

		intList.PushBack(2);
		BOOST_CHECK_EQUAL(intList.GetLastElement(), 2);
		BOOST_CHECK_EQUAL(intList.GetFirstElement(), 2);
	}
	BOOST_AUTO_TEST_CASE(can_be_append_at_start_by_string)
	{
		stringList.PushFront("Some string");
		BOOST_CHECK_EQUAL(stringList.GetLastElement(), "Some string");
		BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "Some string");

		intList.PushFront(2);
		BOOST_CHECK_EQUAL(intList.GetLastElement(), 2);
		BOOST_CHECK_EQUAL(intList.GetFirstElement(), 2);
	}
	struct _when_list_is_not_empty : MyListFixture
	{
		_when_list_is_not_empty()
		{
			stringList.PushBack("Some string 1");
			stringList.PushBack("Some string 2");

			intList.PushBack(1);
			intList.PushBack(2);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_list_is_not_empty, _when_list_is_not_empty)
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "Some string 1");
			stringList.Clear();
			BOOST_CHECK(stringList.IsEmpty());
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "");
			
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 1);
			intList.Clear();
			BOOST_CHECK(intList.IsEmpty());
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_create_new_list_by_copy_old)
		{
			CMyList<std::string> newStringList = CMyList<std::string>(stringList);
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(newStringList.GetLastElement(), "Some string 2");
			newStringList.Clear();
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(stringList.GetLastElement(), "Some string 2");

			CMyList<int> newIntList = CMyList<int>(intList);
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(newIntList.GetLastElement(), 2);
			newIntList.Clear();
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 0);
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(intList.GetLastElement(), 2);
		}
		BOOST_AUTO_TEST_CASE(can_create_new_list_by_move_old)
		{
			CMyList<std::string> newStringList = CMyList<std::string>(std::move(stringList));
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(newStringList.GetLastElement(), "Some string 2");
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(stringList.GetLastElement(), "");

			CMyList<int> newIntList = CMyList<int>(std::move(intList));
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(newIntList.GetLastElement(), 2);
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 0);
			BOOST_CHECK_EQUAL(intList.GetLastElement(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_be_assigned_by_llink)
		{
			CMyList<std::string> newStringList = stringList;
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(newStringList.GetLastElement(), "Some string 2");
			newStringList.Clear();
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(stringList.GetLastElement(), "Some string 2");
		
			CMyList<int> newIntList = intList;
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(newIntList.GetLastElement(), 2);
			newIntList.Clear();
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 0);
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(intList.GetLastElement(), 2);

		}
		BOOST_AUTO_TEST_CASE(can_be_assigned_by_rlink)
		{
			auto newStringList = std::move(stringList);
			BOOST_CHECK_EQUAL(newStringList.GetFirstElement(), "Some string 1");
			BOOST_CHECK_EQUAL(newStringList.GetLastElement(), "Some string 2");
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(stringList.GetLastElement(), "");

			auto newIntList = std::move(intList);
			BOOST_CHECK_EQUAL(newIntList.GetFirstElement(), 1);
			BOOST_CHECK_EQUAL(newIntList.GetLastElement(), 2);
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 0);
			BOOST_CHECK_EQUAL(intList.GetLastElement(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_be_used_vith_ranged_based_for)
		{
			size_t i = 0;
			for (auto el : stringList)
			{
				++i;
				BOOST_CHECK_EQUAL(el, ("Some string " + std::to_string(i)));
			}
			i = 0;
			for (const auto & el : stringList)
			{
				++i;
				BOOST_CHECK_EQUAL(el, ("Some string " + std::to_string(i)));
			}

			i = 0;
			for (auto el : intList)
			{
				++i;
				BOOST_CHECK_EQUAL(el, i);
			}
			i = 0;
			for (const auto & el : intList)
			{
				++i;
				BOOST_CHECK_EQUAL(el, i);
			}
		}
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_begin)
		{
			auto strIt = stringList.begin();
			BOOST_CHECK_EQUAL(*strIt, "Some string 1");

			auto intIt = intList.begin();
			BOOST_CHECK_EQUAL(*intIt, 1);
		}
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_end)
		{
			auto strIt = stringList.end();
			BOOST_CHECK_THROW(*strIt, std::logic_error);

			auto intIt = intList.end();
			BOOST_CHECK_THROW(*intIt, std::logic_error);
		}
		BOOST_AUTO_TEST_CASE(can_create_reverse_iterator_to_begin)
		{
			auto strIt = stringList.rbegin();
			BOOST_CHECK_EQUAL(*strIt, "Some string 2");

			auto intIt = intList.rbegin();
			BOOST_CHECK_EQUAL(*intIt, 2);
		}
		BOOST_AUTO_TEST_CASE(can_create_reverse_iterator_to_end)
		{
			auto strIt = stringList.rend();
			BOOST_CHECK_THROW(*strIt, std::logic_error);

			auto intIt = intList.rend();
			BOOST_CHECK_THROW(*intIt, std::logic_error);
		}
		struct CMyListIteratorFixture : _when_list_is_not_empty
		{
			CMyListIteratorFixture()
				: beginStr(stringList.begin()), endStr(stringList.end()),
				cbeginStr(stringList.cbegin()), cendStr(stringList.cend()),
				rbeginStr(stringList.rbegin()), rendStr(stringList.rend()),
				crbeginStr(stringList.crbegin()), crendStr(stringList.crend()),
				beginInt(intList.begin()), endInt(intList.end()),
				cbeginInt(intList.cbegin()), cendInt(intList.cend()),
				rbeginInt(intList.rbegin()), rendInt(intList.rend()),
				crbeginInt(intList.crbegin()), crendInt(intList.crend()) {};
			CMyList<std::string>::CIterator<std::string> beginStr;
			CMyList<std::string>::CIterator<std::string> endStr;
			CMyList<std::string>::CIterator<const std::string> cbeginStr;
			CMyList<std::string>::CIterator<const std::string> cendStr;
			std::reverse_iterator<CMyList<std::string>::CIterator<std::string>> rbeginStr;
			std::reverse_iterator<CMyList<std::string>::CIterator<std::string>> rendStr;
			std::reverse_iterator<CMyList<std::string>::CIterator<const std::string>> crbeginStr;
			std::reverse_iterator<CMyList<std::string>::CIterator<const std::string>> crendStr;
			CMyList<int>::CIterator<int> beginInt;
			CMyList<int>::CIterator<int> endInt;
			CMyList<int>::CIterator<const int> cbeginInt;
			CMyList<int>::CIterator<const int> cendInt;
			std::reverse_iterator<CMyList<int>::CIterator<int>> rbeginInt;
			std::reverse_iterator<CMyList<int>::CIterator<int>> rendInt;
			std::reverse_iterator<CMyList<int>::CIterator<const int>> crbeginInt;
			std::reverse_iterator<CMyList<int>::CIterator<const int>> crendInt;
		};
		BOOST_FIXTURE_TEST_SUITE(CString_list_iterator, CMyListIteratorFixture)
			BOOST_AUTO_TEST_CASE(throw_exeption_if_try_to_get_end_iterator_value)
			{
				BOOST_CHECK_THROW(*endStr, std::logic_error);
				BOOST_CHECK_THROW(*cendStr, std::logic_error);
				BOOST_CHECK_THROW(*rendStr, std::logic_error);
				BOOST_CHECK_THROW(*crendStr, std::logic_error);

				BOOST_CHECK_THROW(*endInt, std::logic_error);
				BOOST_CHECK_THROW(*cendInt, std::logic_error);
				BOOST_CHECK_THROW(*rendInt, std::logic_error);
				BOOST_CHECK_THROW(*crendInt, std::logic_error);
			}
			BOOST_AUTO_TEST_CASE(can_be_incremented)
			{
				beginStr++;
				cbeginStr++;
				rbeginStr++;
				crbeginStr++;
				BOOST_CHECK_EQUAL(*beginStr, "Some string 2");
				BOOST_CHECK_EQUAL(*cbeginStr, "Some string 2");
				BOOST_CHECK_EQUAL(*rbeginStr, "Some string 1");
				BOOST_CHECK_EQUAL(*crbeginStr, "Some string 1");

				beginInt++;
				cbeginInt++;
				rbeginInt++;
				crbeginInt++;
				BOOST_CHECK_EQUAL(*beginInt, 2);
				BOOST_CHECK_EQUAL(*cbeginInt, 2);
				BOOST_CHECK_EQUAL(*rbeginInt, 1);
				BOOST_CHECK_EQUAL(*crbeginInt, 1);
			}
			BOOST_AUTO_TEST_CASE(can_be_decremented)
			{
				endStr--;
				cendStr--;
				rendStr--;
				crendStr--;
				BOOST_CHECK_EQUAL(*endStr, "Some string 2");
				BOOST_CHECK_EQUAL(*cendStr, "Some string 2");
				BOOST_CHECK_EQUAL(*rendStr, "Some string 1");
				BOOST_CHECK_EQUAL(*crendStr, "Some string 1");

				endInt--;
				cendInt--;
				rendInt--;
				crendInt--;
				BOOST_CHECK_EQUAL(*endInt, 2);
				BOOST_CHECK_EQUAL(*cendInt, 2);
				BOOST_CHECK_EQUAL(*rendInt, 1);
				BOOST_CHECK_EQUAL(*crendInt, 1);
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_when_out_of_range)
			{
				BOOST_CHECK_THROW(beginStr--, std::logic_error);
				BOOST_CHECK_THROW(cbeginStr--, std::logic_error);
				BOOST_CHECK_THROW(rbeginStr--, std::logic_error);
				BOOST_CHECK_THROW(crbeginStr--, std::logic_error);
				BOOST_CHECK_THROW(endStr++, std::logic_error);
				BOOST_CHECK_THROW(cendStr++, std::logic_error);
				BOOST_CHECK_THROW(rendStr++, std::logic_error);
				BOOST_CHECK_THROW(crendStr++, std::logic_error);	

				BOOST_CHECK_THROW(beginInt--, std::logic_error);
				BOOST_CHECK_THROW(cbeginInt--, std::logic_error);
				BOOST_CHECK_THROW(rbeginInt--, std::logic_error);
				BOOST_CHECK_THROW(crbeginInt--, std::logic_error);
				BOOST_CHECK_THROW(endInt++, std::logic_error);
				BOOST_CHECK_THROW(cendInt++, std::logic_error);
				BOOST_CHECK_THROW(rendInt++, std::logic_error);
				BOOST_CHECK_THROW(crendInt++, std::logic_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_CASE(can_insert_element_in_iterator_pos)
		{
			stringList.Insert(stringList.end(), "New string");
			BOOST_CHECK_EQUAL(stringList.GetLastElement(), "New string");
			stringList.Insert(stringList.begin(), "New string");
			BOOST_CHECK_EQUAL(stringList.GetFirstElement(), "New string");
		
			intList.Insert(intList.end(), 3);
			BOOST_CHECK_EQUAL(intList.GetLastElement(), 3);
			intList.Insert(intList.begin(), 0);
			BOOST_CHECK_EQUAL(intList.GetFirstElement(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()