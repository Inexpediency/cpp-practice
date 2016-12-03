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

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	
	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();
	
	CMyString operator=(CMyString & argument);
	CMyString operator=(CMyString && argument);
	CMyString operator+=(CMyString argument);
	char & operator[](size_t index);
	char operator[](size_t index) const;

	//��������� ����������� ������ ���������� ��� �������� ������
	void SetMoved();

	//��������
	class CIterator
	{
	public:
		CIterator() = default;
		CMyString::CIterator::CIterator(char * element, char * begin, char * end)
			:m_element(element), m_begin(begin), m_end(end) {}
		CMyString::CIterator::CIterator(CIterator & other)
			: m_element(other.GetElement()), m_begin(other.GetBegin()), m_end(other.GetEnd()) {}
		char * GetBegin() const;
		char * GetEnd() const;
		char * GetElement() const;
		bool operator==(CIterator other) const;
		bool operator!=(CIterator other) const;
		CMyString::CIterator & operator++();
		CMyString::CIterator operator++(int);
		CMyString::CIterator & operator--();
		CMyString::CIterator operator--(int);
		char & operator*() const;
	private:
		char * m_element = nullptr;
		char * m_end = nullptr;
		char * m_begin = nullptr;
	};

	//��������� �������� �� ������ ������
	CMyString::CIterator begin() const;

	//��������� �������� �� ����� ������
	CMyString::CIterator end() const;
private:
	bool m_isMoved = false;
	char * m_bufferPtr = nullptr;
	size_t m_bufferSize = 0;
	size_t m_length = 0;
};


CMyString operator+(CMyString argument1, CMyString argument2);
bool operator==(CMyString argument1, CMyString argument2);
bool operator!=(CMyString argument1, CMyString argument2);
bool operator<(CMyString argument1, CMyString argument2);
bool operator<=(CMyString argument1, CMyString argument2);
bool operator>(CMyString argument1, CMyString argument2);
bool operator>=(CMyString argument1, CMyString argument2);