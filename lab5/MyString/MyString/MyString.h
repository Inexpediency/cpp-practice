#pragma once
#include <string>
class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char * pString);

	// конструктор, инициализирующий строку данными из 
	// символьного массива заданной длины
	CMyString(const char * pString, size_t length);

	// конструктор копирования
	CMyString(const CMyString & other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString && other);

	// конструктор, инициализирующий строку данными из 
	// строки стандартной библиотеки C++
	CMyString(const std::string & stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength()const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	
	// очистка строки (строка становится снова нулевой длины)
	void Clear();
	
	CMyString operator=(CMyString & argument);
	CMyString operator=(CMyString && argument);
	CMyString operator+=(CMyString argument);
	char & operator[](size_t index);
	char operator[](size_t index) const;

	//запрещает освобождать память выделенную под хранение строки
	void SetMoved();

	//итератор
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

	//возращает итератор на начало строки
	CMyString::CIterator begin() const;

	//возращает итератор на конец строки
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