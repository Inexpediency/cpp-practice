#include "stdafx.h"
#include "MyString.h"

char * AllocateEndLine()
{
	char * ptr = new char[1];
	*ptr = '\0';
	return ptr;
}

CMyString::CMyString()
{
	m_bufferPtr = AllocateEndLine();
	m_bufferSize = sizeof(char);
}

CMyString::CMyString(const char * pString)
{
	if (pString)
	{
		m_length = strlen(pString);
		m_bufferSize = (m_length + 1) * sizeof(char);
		m_bufferPtr = new char[m_length + 1];
		memcpy(m_bufferPtr, pString, m_bufferSize);
	}
	else
	{
		m_bufferPtr = AllocateEndLine();
		m_bufferSize = sizeof(char);
	}
}

CMyString::CMyString(const char * pString, size_t length)
{
	if (pString && length > 0)
	{
		m_length = length;
		m_bufferSize = (m_length + 1) * sizeof(char);
		m_bufferPtr = new char[m_length + 1];
		memcpy(m_bufferPtr, pString, m_bufferSize - sizeof(char));
		m_bufferPtr[m_length] = '\0';
	}
	else
	{
		m_bufferPtr = AllocateEndLine();
		m_bufferSize = sizeof(char);
	}
}

CMyString::CMyString(const CMyString & other)
{
	m_length = other.GetLength();
	m_bufferSize = (m_length + 1) * sizeof(char);
	m_bufferPtr = new char[m_length + 1];
	memcpy(m_bufferPtr, other.GetStringData(), m_bufferSize);
}

CMyString::CMyString(CMyString && other)
{
	m_length = other.GetLength();
	m_bufferSize = (m_length + 1) * sizeof(char);
	m_bufferPtr = const_cast<char*>(other.GetStringData());
	other = "";
}

CMyString::CMyString(const std::string & stlString)
{
	m_length = stlString.length();
	m_bufferSize = (m_length + 1) * sizeof(char);
	m_bufferPtr = new char[m_length + 1];
	memcpy(m_bufferPtr, stlString.c_str(), m_bufferSize);
}

const char * CMyString::GetStringData() const
{
	return m_bufferPtr;
}

CMyString CMyString::SubString(size_t start, size_t length)const
{
	length = length < m_length ? length : m_length;
	if ((m_length - start) >= length && start < m_length)
	{
		return CMyString(m_bufferPtr + start, length);
	}
	return CMyString();
}

size_t CMyString::GetLength() const
{
	return m_length;
}

void CMyString::Clear()
{
	free(m_bufferPtr);
	m_bufferSize = 0;
	m_length = 0;
}

CMyString::~CMyString()
{
	Clear();
}

CMyString & CMyString::operator=(const CMyString & arg)
{
	if (&arg != this)
	{
		Clear();
		m_length = arg.GetLength();
		m_bufferSize = (m_length + 1) * sizeof(char);
		m_bufferPtr = new char[m_length + 1];
		memcpy(m_bufferPtr, arg.GetStringData(), m_bufferSize);
	}
	return *this;
}

CMyString & CMyString::operator=(CMyString && arg)
{
	if (&arg != this)
	{
		Clear();
		m_length = arg.GetLength();
		m_bufferSize = (m_length + 1) * sizeof(char);
		m_bufferPtr = const_cast<char*>(arg.GetStringData());
		arg = "";
	}
	return *this;
}

CMyString && operator+(const CMyString & arg1, const CMyString & arg2)
{
	size_t newStrLen = arg1.GetLength() + arg2.GetLength();
	std::shared_ptr<char> temp(new char[newStrLen]);
	memcpy(temp.get(), arg1.GetStringData(), (arg1.GetLength()) * sizeof(char));
	memcpy(temp.get() + arg1.GetLength() * sizeof(char), arg2.GetStringData(), arg2.GetLength() * sizeof(char));
	return std::move(CMyString(temp.get(), newStrLen));
}

CMyString & CMyString::operator+=(const CMyString & arg)
{
	*this = *this + arg;
	return *this;
}

char & CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::logic_error("incorrect index");
	}
	return m_bufferPtr[index];
};

char & CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::logic_error("incorrect index");
	}
	return m_bufferPtr[index];
}

bool operator==(const CMyString & arg1, const CMyString & arg2)
{
	if (arg1.GetLength() == arg2.GetLength())
	{
		for (size_t i = 0; i < arg2.GetLength(); ++i)
		{
			if (arg1[i] != arg2[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool operator<(const CMyString & arg1, const CMyString & arg2)
{
	size_t length = std::min(arg1.GetLength(), arg2.GetLength());
	for (size_t i = 0; i < length; ++i)
	{
		if (arg1[i] > arg2[i])
		{
			return false;
		}
		if (arg1[i] < arg2[i])
		{
			return true;
		}
	}
	return arg1.GetLength() < arg2.GetLength();
}

bool operator<=(const CMyString & arg1, const CMyString & arg2)
{
	size_t length = std::min(arg1.GetLength(), arg2.GetLength());
	for (size_t i = 0; i < length; ++i)
	{
		if (arg1[i] > arg2[i])
		{
			return false;
		}
		if (arg1[i] < arg2[i])
		{
			return true;
		}
	}
	return arg1.GetLength() <= arg2.GetLength();
}

bool operator>(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 <= arg2);
}

bool operator>=(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 < arg2);
}

bool operator!=(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 == arg2);
}

char * CMyString::CIterator::GetBegin() const
{
	return m_begin;
}
char * CMyString::CIterator::GetEnd() const
{
	return m_end;
}
char * CMyString::CIterator::GetElement() const
{
	return m_element;
}

bool CMyString::CIterator::operator==(CIterator other) const
{
	return m_element == other.GetElement();
}

bool CMyString::CIterator::operator!=(CIterator other) const
{
	return !(*this == other);
}

CMyString::CIterator CMyString::begin() const
{
	char * end = m_bufferPtr + m_bufferSize - 1;
	return CMyString::CIterator(m_bufferPtr, m_bufferPtr, end);
}

CMyString::CIterator CMyString::end() const
{
	char * end = m_bufferPtr + m_bufferSize - 1;
	return CMyString::CIterator(end, m_bufferPtr, end);
}

CMyString::CIterator & CMyString::CIterator::operator++()
{
	++m_element;
	if (m_element > m_end)
	{
		--m_element;
		throw std::out_of_range("Iterator out of range");
	}
	return *this;
}

CMyString::CIterator CMyString::CIterator::operator++(int)
{
	auto copy = *this;
	++*this;
	return copy;
}

CMyString::CIterator & CMyString::CIterator::operator--()
{
	--m_element;
	if (m_element < m_begin)
	{
		++m_element;
		throw std::out_of_range("Iterator out of range");
	}
	return *this;
}

CMyString::CIterator CMyString::CIterator::operator--(int)
{
	auto copy = *this;
	--*this;
	return copy;
}

char & CMyString::CIterator::operator*() const
{
	if (m_element == m_end)
	{
		throw std::logic_error("Can not get end iteratator value");
	}
	return *m_element;
}