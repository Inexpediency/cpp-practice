#pragma once
#include <string>

enum Protocol
{

	HTTP = 80,
	HTTPS = 443,
	NO_PROTOCOL,
};

class CHttpUrl
{
public:
	CHttpUrl() = delete;
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	std::invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string document,
		Protocol protocol = HTTP,
		unsigned short port = 80);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � URL �� ������ ����������
	std::string GetURL()const;

	// ���������� �������� ���
	std::string GetDomain()const;

	/*
	���������� ��� ���������. �������:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// ���������� ��� ���������
	Protocol GetProtocol()const;

	// ���������� ����� �����
	unsigned short GetPort()const;
	
	//������������ ������ �� url`� � ������
	std::string ToString()const;
private:
	Protocol m_protocol;
	std::string m_document;
	std::string m_domain;
	unsigned short m_port;
};
