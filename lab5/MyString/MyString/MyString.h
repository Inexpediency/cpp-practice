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

	std::unique_ptr<char[]> & GetUniquePtrToData();

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	
	// очистка строки (строка становится снова нулевой длины)
	void Clear();
	
	CMyString & operator=(const CMyString & argument);
	CMyString & operator=(CMyString && argument);
	CMyString & operator+=(const CMyString & argument);
	char & operator[](size_t index);
	char & operator[](size_t index) const;

	//итератор
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

	//возращает итератор на начало строки
	CMyString::CIterator begin() const;

	//возращает итератор на конец строки
	CMyString::CIterator end() const;

	//возращает константный итератор на начало строки
	CMyString::CConsIterator сbegin() const;

	//возращает константный итератор на конец строки
	CMyString::CConsIterator сend() const;
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