#include "stdafx.h"
#include "../StrigList/StringList.h"

struct StringListFixture
{
	CStringList list = CStringList();
};
BOOST_FIXTURE_TEST_SUITE(CStringList_on_create, StringListFixture)
	BOOST_AUTO_TEST_CASE(empty)
	{
		BOOST_CHECK(list.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(have_zero_length)
	{
		BOOST_CHECK_EQUAL(list.GetSize(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_be_append_at_end_by_string)
	{
		list.PushBack("Some string");
		BOOST_CHECK_EQUAL(list.GetLastElement(), "Some string");
		BOOST_CHECK_EQUAL(list.GetFirstElement(), "Some string");
	}
	BOOST_AUTO_TEST_CASE(can_be_append_at_start_by_string)
	{
		list.PushFront("Some string");
		BOOST_CHECK_EQUAL(list.GetLastElement(), "Some string");
		BOOST_CHECK_EQUAL(list.GetFirstElement(), "Some string");
	}
	struct _when_list_is_not_empty : StringListFixture
	{
		_when_list_is_not_empty()
		{
			list.PushBack("Some string");
			list.PushBack("Some string");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_list_is_not_empty, _when_list_is_not_empty)
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "Some string");
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "");
		}
		BOOST_AUTO_TEST_CASE(can_create_new_list_by_copy_old)
		{
			CStringList newList = CStringList(list);
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(newList.GetLastElement(), "Some string");
			newList.Clear();
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), ""); 
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(list.GetLastElement(), "Some string");
		}
		BOOST_AUTO_TEST_CASE(can_create_new_list_by_move_old)
		{
			CStringList newList = CStringList(std::move(list));
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(newList.GetLastElement(), "Some string");
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(list.GetLastElement(), "");
		}
		BOOST_AUTO_TEST_CASE(can_be_assigned_by_llink)
		{
			CStringList newList = list;
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(newList.GetLastElement(), "Some string");
			newList.Clear();
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(list.GetLastElement(), "Some string");
		}
		BOOST_AUTO_TEST_CASE(can_be_assigned_by_rlink)
		{
			auto newList = std::move(list);
			BOOST_CHECK_EQUAL(newList.GetFirstElement(), "Some string");
			BOOST_CHECK_EQUAL(newList.GetLastElement(), "Some string");
			BOOST_CHECK_EQUAL(list.GetFirstElement(), "");
			BOOST_CHECK_EQUAL(list.GetLastElement(), "");
		}
		BOOST_AUTO_TEST_CASE(can_be_used_vith_ranged_based_for)
		{
			size_t i = 0;
			for (auto el : list)
			{
				++i;
				BOOST_CHECK_EQUAL(el, "Some string");
			}
			BOOST_CHECK(i = 2);
		}
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_begin)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*it, "Some string");
		}
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_end)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(*it, std::logic_error);
		}
		BOOST_AUTO_TEST_CASE(can_create_reverse_iterator_to_begin)
		{
			auto it = list.rbegin();
			BOOST_CHECK_EQUAL(*it, "Some string");
		}
		BOOST_AUTO_TEST_CASE(can_create_reverse_iterator_to_end)
		{
			auto it = list.rend();
			BOOST_CHECK_THROW(*it, std::logic_error);
		}
		struct CStringListIteratorFixture : _when_list_is_not_empty
		{
			CStringListIteratorFixture()
				: begin(list.begin()), end(list.end()),
				cbegin(list.cbegin()), cend(list.cend()), 
				rbegin(list.rbegin()), rend(list.rend()),
				crbegin(list.crbegin()), crend(list.crend()) {};
			CStringList::CIterator<std::string> begin;
			CStringList::CIterator<std::string> end;
			CStringList::CIterator<const std::string> cbegin;
			CStringList::CIterator<const std::string> cend;
			CStringList::CReverseIterator<std::string> rbegin;
			CStringList::CReverseIterator<std::string> rend;
			CStringList::CReverseIterator<const std::string> crbegin;
			CStringList::CReverseIterator<const std::string> crend;
		};
		BOOST_FIXTURE_TEST_SUITE(CString_list_iterator, CStringListIteratorFixture)
			BOOST_AUTO_TEST_CASE(throw_exeption_if_try_to_get_end_iterator_value)
			{
				BOOST_CHECK_THROW(*end, std::logic_error);
				BOOST_CHECK_THROW(*cend, std::logic_error);
				BOOST_CHECK_THROW(*rend, std::logic_error);
				BOOST_CHECK_THROW(*crend, std::logic_error);
			}
			BOOST_AUTO_TEST_CASE(can_be_incremented)
			{
				begin++;
				cbegin++;
				rbegin++;
				crbegin++;
				BOOST_CHECK_EQUAL(*begin, "Some string");
				BOOST_CHECK_EQUAL(*cbegin, "Some string");
				BOOST_CHECK_EQUAL(*rbegin, "Some string");
				BOOST_CHECK_EQUAL(*crbegin, "Some string");
			}
			BOOST_AUTO_TEST_CASE(can_be_decremented)
			{
				end--;
				cend--;
				rend--;
				crend--;
				BOOST_CHECK_EQUAL(*end, "Some string");
				BOOST_CHECK_EQUAL(*cend, "Some string");
				BOOST_CHECK_EQUAL(*rend, "Some string");
				BOOST_CHECK_EQUAL(*crend, "Some string");
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_when_out_of_range)
			{
				BOOST_CHECK_THROW(begin--, std::logic_error);
				BOOST_CHECK_THROW(cbegin--, std::logic_error);
				BOOST_CHECK_THROW(rbegin--, std::logic_error);
				BOOST_CHECK_THROW(crbegin--, std::logic_error);
				BOOST_CHECK_THROW(end++, std::logic_error);
				BOOST_CHECK_THROW(cend++, std::logic_error);
				BOOST_CHECK_THROW(rend++, std::logic_error);
				BOOST_CHECK_THROW(crend++, std::logic_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()