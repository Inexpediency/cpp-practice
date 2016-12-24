#include "stdafx.h"
#include "StringList.h"

CStringList::CStringList()
{
	Clear();
}

CStringList::CStringList(const CStringList & other)
{
	Clear();
	for (auto i = other.m_begin->next; i != other.m_end; i = i->next)
	{
		PushBack(i->value);
	}
}

CStringList::CStringList(CStringList && other)
{
	Clear();
	std::swap(m_begin, other.m_begin);
	std::swap(m_end, other.m_end);
	std::swap(m_length, other.m_length);
}

void BreakLinks(const std::shared_ptr<ListElement> & listStart)
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

CStringList::~CStringList()
{
	BreakLinks(m_begin);
}
void CStringList::Clear()
{
	BreakLinks(m_begin);
	m_begin->next = m_end;
	m_end->prev = m_begin;
	m_length = 0;
}

bool CStringList::IsEmpty() const
{
	return m_length == 0;
}

size_t CStringList::GetSize() const
{
	return m_length;
}

void CStringList::PushBack(const std::string & string)
{
	auto currentEl = std::make_shared<ListElement>(string, m_end->prev, m_end);
	m_end->prev->next = currentEl;
	m_end->prev = currentEl;
	++m_length;
}

void CStringList::PushFront(const std::string & string)
{
	auto currentEl = std::make_shared<ListElement>(string, m_begin, m_begin->next);
	m_begin->next->prev = currentEl;
	m_begin->next = currentEl;
	++m_length;
}

std::string CStringList::GetLastElement() const
{
	return m_end->prev->value;
}
std::string CStringList::GetFirstElement() const
{
	return m_begin->next->value;
}

CStringList::CIterator<std::string> CStringList::begin()
{
	return CStringList::CIterator<std::string>(m_begin->next);
}
CStringList::CIterator<std::string> CStringList::end()
{
	return CStringList::CIterator<std::string>(m_end);
}
CStringList::CIterator<const std::string> CStringList::begin() const
{
	return CStringList::CIterator<const std::string>(m_begin->next);
}
CStringList::CIterator<const std::string> CStringList::end()  const
{
	return CStringList::CIterator<const std::string>(m_end);
}
CStringList::CIterator<const std::string> CStringList::cbegin() const
{
	return CStringList::CIterator<const std::string>(m_begin->next);
}
CStringList::CIterator<const std::string> CStringList::cend() const
{
	return CStringList::CIterator<const std::string>(m_end);
}


CStringList::CReverseIterator<std::string> CStringList::rbegin()
{
	return CStringList::CReverseIterator<std::string>(m_end->prev);
}
CStringList::CReverseIterator<std::string> CStringList::rend()
{
	return CStringList::CReverseIterator<std::string>(m_begin);
}
CStringList::CReverseIterator<const std::string> CStringList::rbegin() const
{
	return CStringList::CReverseIterator<const std::string>(m_end->prev);
}
CStringList::CReverseIterator<const std::string> CStringList::rend() const
{
	return CStringList::CReverseIterator<const std::string>(m_begin);
}
CStringList::CReverseIterator<const std::string> CStringList::crbegin() const
{
	return CStringList::CReverseIterator<const std::string>(m_end->prev);
}
CStringList::CReverseIterator<const std::string> CStringList::crend() const
{
	return CStringList::CReverseIterator<const std::string>(m_begin);
}