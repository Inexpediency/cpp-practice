#pragma once
#include <string>
#include <memory>

template <typename T>
struct ListElement
{
	ListElement(const T & el, const std::shared_ptr<ListElement> & prev, const std::shared_ptr<ListElement> & next)
		: value(el), prev(prev), next(next) {}
	T value;
	std::shared_ptr<ListElement> next;
	std::shared_ptr<ListElement> prev;
};

template <typename T>
class CMyList
{
public:
	
	CMyList()
	{
		Clear();
	}
	
	CMyList(const CMyList & other)
	{
		Clear();
		for (auto i = other.m_begin->next; i != other.m_end; i = i->next)
		{
			PushBack(i->value);
		}
	}

	CMyList(CMyList && other)
	{
		Clear();
		std::swap(m_begin, other.m_begin);
		std::swap(m_end, other.m_end);
		std::swap(m_length, other.m_length);
	}

	void BreakLinks(const std::shared_ptr<ListElement<T>> & listStart)
	{
		auto current = listStart;
		auto next = listStart->next;
		while (next)
		{
			current->next = nullptr;
			current->prev = nullptr;
			current = next;
			next = current->next;
		}
	}

	size_t GetSize() const
	{
		return m_length;
	}
	
	bool IsEmpty() const
	{
		return m_length == 0;
	}
	
	void Clear()
	{
		BreakLinks(m_begin);
		m_begin->next = m_end;
		m_end->prev = m_begin;
		m_length = 0;
	}
	
	T GetLastElement() const
	{

		return m_end->prev->value;
	}

	T GetFirstElement() const
	{
		return m_begin->next->value;
	}

	void PushBack(const T & el)
	{

		auto currentEl = std::make_shared<ListElement<T>>(el, m_end->prev, m_end);
		m_end->prev->next = currentEl;
		m_end->prev = currentEl;
		++m_length;
	}

	void PushFront(const T & el)
	{
		auto currentEl = std::make_shared<ListElement<T>>(el, m_begin, m_begin->next);
		m_begin->next->prev = currentEl;
		m_begin->next = currentEl;
		++m_length;
	}

	~CMyList()
	{
		BreakLinks(m_begin);
	}

	template <class IterTy>
	class CIterator
	{
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef IterTy value_type;
		typedef ptrdiff_t difference_type;
		typedef IterTy* pointer;
		typedef IterTy& reference;
	public:
		friend class CMyList;
		CIterator() = default;
		CIterator(const CIterator & it) : CIterator<IterTy>(it.m_element) {};
		CIterator(const std::shared_ptr<ListElement<T>> & element) : m_element(element) {};
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
		IterTy & operator*()
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
		std::shared_ptr<ListElement<T>> m_element;
	};

	CIterator<T> begin()
	{
		return CIterator<T>(m_begin->next);
	}
	CIterator<T> end()
	{
		return CIterator<T>(m_end);
	}
	CIterator<const T> begin() const
	{
		return CIterator<const T>(m_begin->next);
	}
	CIterator<const T> end() const
	{
		return CIterator<const T>(m_end);
	}
	CIterator<const T> cbegin() const
	{
		return CIterator<const T>(m_begin->next);
	}
	CIterator<const T> cend() const
	{
		return CIterator<const T>(m_end);
	}

	std::reverse_iterator<CIterator<T>> rbegin()
	{
		return std::reverse_iterator<CIterator<T>>(end());
	}
	std::reverse_iterator<CIterator<T>> rend()
	{
		return std::reverse_iterator<CIterator<T>>(begin());
	}
	std::reverse_iterator<CIterator<const T>> rbegin() const
	{
		return std::reverse_iterator<CIterator<const T>>(cend());
	}
	std::reverse_iterator<CIterator<const T>> rend() const
	{
		return std::reverse_iterator<CIterator<const T>>(cbegin());
	}
	std::reverse_iterator<CIterator<const T>> crbegin() const
	{
		return std::reverse_iterator<CIterator<const T>>(cend());
	}
	std::reverse_iterator<CIterator<const T>> crend() const
	{
		return std::reverse_iterator<CIterator<const T>>(cbegin());
	}

	void Insert(const CIterator<T> & it, const T & el)
	{
		auto currentEl = std::make_shared<ListElement<T>>(el, it.m_element->prev, it.m_element);
		it.m_element->prev->next = currentEl;
		it.m_element->prev = currentEl;
		++m_length;
	}

	void Insert(const CIterator<const T> & it, const T & el)
	{
		auto currentEl = std::make_shared<ListElement<T>>(el, it.m_element->prev, it.m_element);
		it.m_element->prev->next = currentEl;
		it.m_element->prev = currentEl;
		++m_length;
	}
private:
	size_t m_length = 0;
	std::shared_ptr<ListElement<T>> m_begin = std::make_shared<ListElement<T>>(T(), nullptr, nullptr);
	std::shared_ptr<ListElement<T>> m_end = std::make_shared<ListElement<T>>(T(), nullptr, nullptr);
};
