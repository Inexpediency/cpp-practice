#pragma once
#include <string>
#include <memory>

struct ListElement
{
	ListElement(const std::string & str, const std::shared_ptr<ListElement> & prev, const std::shared_ptr<ListElement> & next)
		: value(str), prev(prev), next(next) {}
	std::string value;
	std::shared_ptr<ListElement> next;
	std::shared_ptr<ListElement> prev;
};

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList & other);
	CStringList(CStringList && other);
	size_t GetSize() const;
	bool IsEmpty() const;
	void Clear();
	std::string GetLastElement() const;
	std::string GetFirstElement() const;
	void PushBack(const std::string & string);
	void PushFront(const std::string & string);
	~CStringList();

	template <class T>
	class CIterator
	{
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	public:
		friend class CStringList;
		CIterator() = default;
		CIterator(const CIterator & it) : CIterator<T>(it.m_element) {};
		CIterator(const std::shared_ptr<ListElement> & element) : m_element(element) {};
		CIterator & operator=(const CIterator & other)
		{
			m_element = other.m_element;
		}
		bool operator==(const CIterator & other) const
		{
			return m_element == other.m_element;
		}
		bool operator!=(const CIterator & other) const
		{
			return m_element != other.m_element;
		}
		T & operator*()
		{
			if (!m_element->next || !m_element->prev)
			{
				throw std::logic_error("can not end or rend iterator value");
			}
			return m_element->value;
		}
		CIterator & operator++()
		{
			if (!m_element->next)
			{
				throw std::logic_error("iterator out of range");
			}
			m_element = m_element->next;
			return *this;
		}
		const CIterator operator++(int)
		{
			auto copy = *this;
			++*this;
			return copy;
		}
		CIterator & operator--()
		{
			if (!m_element->prev || !m_element->prev->prev)
			{
				throw std::logic_error("iterator out of range");
			}
			m_element = m_element->prev;
			return *this;
		}
		const CIterator operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}
	private:
		std::shared_ptr<ListElement> m_element;
	};
	CIterator<std::string> begin();
	CIterator<std::string> end();
	CIterator<const std::string> begin() const;
	CIterator<const std::string> end() const;
	CIterator<const std::string> cbegin() const;
	CIterator<const std::string> cend() const;
	std::reverse_iterator<CIterator<std::string>> rbegin();
	std::reverse_iterator<CIterator<std::string>> rend();
	std::reverse_iterator<CIterator<const std::string>> rbegin() const;
	std::reverse_iterator<CIterator<const std::string>> rend() const;
	std::reverse_iterator<CIterator<const std::string>> crbegin() const;
	std::reverse_iterator<CIterator<const std::string>> crend() const;
	template<class T>
	void Insert(const CIterator<T> & it, const std::string & string)
	{
		auto currentEl = std::make_shared<ListElement>(string, it.m_element->prev, it.m_element);
		it.m_element->prev->next = currentEl;
		it.m_element->prev = currentEl;
		++m_length;
	}
private:
	size_t m_length = 0;
	std::shared_ptr<ListElement> m_begin = std::make_shared<ListElement>("", nullptr, nullptr);
	std::shared_ptr<ListElement> m_end = std::make_shared<ListElement>("", nullptr, nullptr);
};
