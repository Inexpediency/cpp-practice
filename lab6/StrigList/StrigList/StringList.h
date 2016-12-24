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
	class CBaseIterator
	{
	public:
		CBaseIterator(const std::shared_ptr<ListElement> & element) : m_element(element) {};
		bool operator==(const CBaseIterator & other) const
		{
			return m_element == other.m_element;
		}
		bool operator!=(const CBaseIterator & other) const
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
		virtual ~CBaseIterator() = default;
	protected:
		std::shared_ptr<ListElement> m_element;
	};

	template <class T>
	class CIterator : public CBaseIterator<T>
	{
	public:
		friend class CStringList;
		CIterator(const std::shared_ptr<ListElement> & element) : CBaseIterator<T>(element) {};
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
	};

	template <class T>
	class CReverseIterator : public CBaseIterator<T>
	{
	public:
		CReverseIterator(const std::shared_ptr<ListElement> & element) : CBaseIterator<T>(element) {};
		CReverseIterator & operator++()
		{
			if (m_element->prev == nullptr)
			{
				throw std::logic_error("iterator out of range");
			}
			m_element = m_element->prev;
			return *this;
		}
		const CReverseIterator operator++(int)
		{
			auto copy = *this;
			++*this;
			return copy;
		}
		CReverseIterator & operator--()
		{
			if (m_element->next == nullptr || !m_element->next->next)
			{
				throw std::logic_error("iterator out of range");
			}
			m_element = m_element->next;
			return *this;
		}
		const CReverseIterator operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}
	};
	CIterator<std::string> begin();
	CIterator<std::string> end();
	CIterator<const std::string> begin() const;
	CIterator<const std::string> end() const;
	CIterator<const std::string> cbegin() const;
	CIterator<const std::string> cend() const;
	CReverseIterator<std::string> rbegin();
	CReverseIterator<std::string> rend();
	CReverseIterator<const std::string> rbegin() const;
	CReverseIterator<const std::string> rend() const;
	CReverseIterator<const std::string> crbegin() const;
	CReverseIterator<const std::string> crend() const;
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
