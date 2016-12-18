#pragma once
#include <string>
class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char * pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char * pString, size_t length);

	// ����������� �����������
	CMyString(const CMyString & other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString && other);

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(const std::string & stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	// ������ ����������� ���������� unique_ptr
	~CMyString() = default;

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	
	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();
	
	CMyString & operator=(const CMyString & argument);
	CMyString & operator=(CMyString && argument);
	CMyString & operator+=(const CMyString & argument);
	char & operator[](size_t index);
	const char & operator[](size_t index) const;
	friend CMyString operator+(const CMyString & argument1, const CMyString & argument2);
	friend bool operator==(const CMyString & argument1, const CMyString & argument2);
	friend bool operator!=(const CMyString & argument1, const CMyString & argument2);
	friend bool operator<(const CMyString & argument1, const CMyString & argument2);
	friend bool operator<=(const CMyString & argument1, const CMyString & argument2);
	friend bool operator>(const CMyString & argument1, const CMyString & argument2);
	friend bool operator>=(const CMyString & argument1, const CMyString & argument2);

	//��������
	template <typename T>
	class CIterator
	{
	public:
		CIterator() = default;
		CIterator(T * element, T * begin, T * end)
			:m_element(element), m_begin(begin), m_end(end) {}
		CIterator(CIterator & other)
			: m_element(other.m_element), m_begin(other.m_begin), m_end(other.m_end) {}
		bool operator==(const CIterator & other) const
		{
			return m_element == other.m_element;
		}
		bool operator!=(const CIterator & other) const
		{
			return !(*this == other);
		}
		CIterator operator+(ptrdiff_t n)
		{
			if (m_element + n < m_begin || m_element + n > m_end)
			{
				throw std::out_of_range("Iterator out of range");
			}
			return CIterator<T>(m_element + n, m_begin, m_end);
		}
		CIterator operator-(ptrdiff_t n)
		{
			if (m_element - n < m_begin || m_element - n > m_end)
			{
				throw std::out_of_range("Iterator out of range");
			}
			return CIterator<T>(m_element - n, m_begin, m_end);
		};
		friend CIterator operator+(ptrdiff_t n, const CIterator & other)
		{
			if (other.m_element + n < other.m_begin || other.m_element + n > other.m_end)
			{
				throw std::out_of_range("Iterator out of range");
			}
			return CIterator<T>(other.m_element + n, other.m_begin, other.m_end);
		}
		friend CIterator operator-(ptrdiff_t n, const CIterator & other)
		{
			if (n - other.m_element < other.m_begin || n - other.m_element > other.m_end)
			{
				throw std::out_of_range("Iterator out of range");
			}
			return CIterator<T>(n - other.m_element, other.m_begin, other.m_end);
		};
		CIterator & operator-=(ptrdiff_t n)
		{
			*this = operator-(n);
			return *this;
		};
		CIterator & operator+=(ptrdiff_t n)
		{
			*this = operator+(n);
			return *this;
		};
		CIterator & operator++()
		{
			if (m_element == m_end)
			{
				throw std::out_of_range("Iterator out of range");
			}
			++m_element;
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
			if (m_element == m_begin)
			{
				throw std::out_of_range("Iterator out of range");
			}
			--m_element;
			return *this;
		}
		const CIterator operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}
		T & operator*() const
		{
			if (m_element == m_end)
			{
				throw std::logic_error("Iterator is out of range");
			}
			return *m_element;
		}
		~CIterator() = default;
	protected:
		T * m_element = nullptr;
		T * m_end = nullptr;
		T * m_begin = nullptr;
	};

	//��������� �������� �� ������ ������
	CMyString::CIterator<char> begin() const;

	//��������� �������� �� ����� ������
	CMyString::CIterator<char> end() const;

	//��������� ����������� �������� �� ������ ������
	CMyString::CIterator<const char> cbegin() const;

	//��������� ����������� �������� �� ����� ������
	CMyString::CIterator<const char> cend() const;
private:
	CMyString(std::unique_ptr<char[]> & memoryBlock, size_t len);
private:
	std::unique_ptr<char[]> m_bufferPtr = nullptr;
	size_t m_bufferSize = 0;
	size_t m_length = 0;
};