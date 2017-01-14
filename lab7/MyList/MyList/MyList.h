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

	T & GetLastElement()
	{
		return m_end->prev->value;
	}

	T & GetFirstElement()
	{
		return m_begin->next->value;
	}
	
	const T & GetLastElement() const
	{
		return m_end->prev->value;
	}

	const T & GetFirstElement() const
	{
		return m_begin->next->value;
	}

	void PushBack(const T & el)
	{
		Insert(end(), el);
	}

	void PushFront(const T & el)
	{
		Insert(begin(), el);
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
		explicit CIterator(const std::shared_ptr<ListElement<T>> & element) : m_element(element) {};
		operator CIterator<const IterTy>() 
		{
			return CIterator<const IterTy>(m_element);
		};
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
		IterTy & operator*() const
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

	typedef CIterator<T> IteratorType;
	typedef CIterator<const T> ContIteratorType;
	typedef std::reverse_iterator<CIterator<T>> RevIteratorType;
	typedef std::reverse_iterator<CIterator<const T>> ContRevIteratorType;

	IteratorType begin()
	{
		return IteratorType(m_begin->next);
	}
	IteratorType end()
	{
		return IteratorType(m_end);
	}
	ContIteratorType begin() const
	{
		return ContIteratorType(m_begin->next);
	}
	ContIteratorType end() const
	{
		return ContIteratorType(m_end);
	}
	ContIteratorType cbegin() const
	{
		return ContIteratorType(m_begin->next);
	}
	ContIteratorType cend() const
	{
		return CIterator<const T>(m_end);
	}

	RevIteratorType rbegin()
	{
		return RevIteratorType(end());
	}
	RevIteratorType rend()
	{
		return RevIteratorType(begin());
	}
	ContRevIteratorType rbegin() const
	{
		return ContRevIteratorType(cend());
	}
	ContRevIteratorType rend() const
	{
		return ContRevIteratorType(cbegin());
	}
	ContRevIteratorType crbegin() const
	{
		return ContRevIteratorType(cend());
	}
	ContRevIteratorType crend() const
	{
		return ContRevIteratorType(cbegin());
	}

	void Insert(const ContIteratorType & it, const T & el)
	{
		auto currentEl = std::make_shared<ListElement<T>>(el, it.m_element->prev, it.m_element);
		it.m_element->prev->next = currentEl;
		it.m_element->prev = currentEl;
		++m_length;
	}
private:
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
private:
	size_t m_length = 0;
	std::shared_ptr<ListElement<T>> m_begin = std::make_shared<ListElement<T>>(T(), nullptr, nullptr);
	std::shared_ptr<ListElement<T>> m_end = std::make_shared<ListElement<T>>(T(), nullptr, nullptr);
};
