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
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	std::unique_ptr<char[]> & GetUniquePtrToData();

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	
	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();
	
	CMyString & operator=(const CMyString & argument);
	CMyString & operator=(CMyString && argument);
	CMyString & operator+=(const CMyString & argument);
	char & operator[](size_t index);
	char & operator[](size_t index) const;

	//��������
	class CIterator
	{
	public:
		CIterator() = default;
		CIterator(char * element, char * begin, char * end)
			:m_element(element), m_begin(begin), m_end(end) {}
		CIterator(CIterator & other)
			: m_element(other.GetElement()), m_begin(other.GetBegin()), m_end(other.GetEnd()) {}
		char * GetBegin() const;
		char * GetEnd() const;
		char * GetElement() const;
		bool operator==(CIterator other) const;
		bool operator!=(CIterator other) const;
		CMyString::CIterator & operator+(size_t n);
		CMyString::CIterator & operator-(size_t n);
		CMyString::CIterator & operator++();
		CMyString::CIterator operator++(int);
		CMyString::CIterator & operator--();
		CMyString::CIterator operator--(int);
		char & operator*() const;
		~CIterator() = default;
	protected:
		char * m_element = nullptr;
		char * m_end = nullptr;
		char * m_begin = nullptr;
	};

	class CConsIterator : public CIterator
	{
	public:
		CConsIterator() = default;
		CConsIterator(char * element, char * begin, char * end)
			:CMyString::CIterator(element, begin, end) {};
		CConsIterator(CIterator & other)
			:CMyString::CIterator(other) {};
		char operator*() const;
	};

	//��������� �������� �� ������ ������
	CMyString::CIterator begin() const;

	//��������� �������� �� ����� ������
	CMyString::CIterator end() const;

	//��������� ����������� �������� �� ������ ������
	CMyString::CConsIterator �begin() const;

	//��������� ����������� �������� �� ����� ������
	CMyString::CConsIterator �end() const;
private:
	std::unique_ptr<char[]> m_bufferPtr = nullptr;
	size_t m_bufferSize = 0;
	size_t m_length = 0;
};


CMyString operator+(const CMyString & argument1, const CMyString & argument2);
bool operator==(const CMyString & argument1, const CMyString & argument2);
bool operator!=(const CMyString & argument1, const CMyString & argument2);
bool operator<(const CMyString & argument1, const CMyString & argument2);
bool operator<=(const CMyString & argument1, const CMyString & argument2);
bool operator>(const CMyString & argument1, const CMyString & argument2);
bool operator>=(const CMyString & argument1, const CMyString & argument2);