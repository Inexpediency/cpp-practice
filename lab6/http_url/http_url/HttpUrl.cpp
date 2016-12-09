#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

const std::string PROTOCOL_PATTERN = "((https)|(http))";
const std::string DOMAIN_PATTERN = "(((\\w|-)+\\.)+\\w+)";
const std::string DOCUMEN_PATTERN = "(((/(\\w|-|\\.|_)+)+/?)|/)";
const std::string QUERY_STRING = "(\\?.*)?";

Protocol StringToProtocol(const std::string & protocol)
{
	if (protocol == "http")
		return Protocol::HTTP;
	else if (protocol == "https")
		return Protocol::HTTPS;
	else return Protocol::NO_PROTOCOL;
}

std::string ProtocolToString(Protocol protocol)
{
	if (protocol == Protocol::HTTP)
return "http";
	else if (protocol == Protocol::HTTPS)
		return "https";
	else return "No recognized protocol";
}

std::string ToLowCase(std::string str)
{
	std::locale loc;
	for (auto & ch : str)
	{
		ch = std::tolower(ch, loc);
	}
	return str;
}

Protocol CutProtocol(std::string & url)
{
	if (std::regex_match(url, std::regex(PROTOCOL_PATTERN + ".*")))
	{
		std::string protocol = url.substr(0, url.find("://"));
		url.erase(0, protocol.length() + 3);
		return StringToProtocol(protocol);
	}
	throw CUrlParsingError("Invalid protocol");
}

std::string CutDomain(std::string & url)
{
	if (std::regex_match(url, std::regex(DOMAIN_PATTERN + ".*")))
	{
		auto hostEndPos = url.find(":");
		hostEndPos = hostEndPos == std::string::npos ? url.find("/") : hostEndPos;
		hostEndPos = hostEndPos == std::string::npos ? url.length() : hostEndPos;
		std::string host = url.substr(0, hostEndPos);
		url.erase(0, hostEndPos);
		return host;
	}
	throw CUrlParsingError("Invalid domain");
}

std::string CutPort(std::string & url)
{
	if (std::regex_match(url, std::regex("(:\\d+)?($|\\?.*|/.*)")))
	{
		if ((url.length() >= 1) && url[0] == ':')
		{
			url.erase(0, 1);
		}
		auto portEndPos = url.find("/");
		portEndPos = portEndPos == std::string::npos ? url.length() : portEndPos;
		std::string port = url.substr(0, portEndPos);
		url.erase(0, port.length());
		return port;
	}
	throw CUrlParsingError("Invalid port");
}

CHttpUrl::CHttpUrl(const std::string & url)
{
	std::string tempUrl = ToLowCase(url);
	m_protocol = CutProtocol(tempUrl);
	m_domain = CutDomain(tempUrl);
	std::string port = CutPort(tempUrl);
	m_port = port == "" ? static_cast<int>(m_protocol) : std::stoi(port);
	if (tempUrl.length() == 0 || tempUrl[0] == '?')
	{
		tempUrl = "/" + tempUrl;
	}
	if (std::regex_match(tempUrl, std::regex(DOCUMEN_PATTERN + QUERY_STRING)))
		m_document = tempUrl;
	else
		throw CUrlParsingError("Invalid document");
}

CHttpUrl::CHttpUrl(
	const std::string & domain,
	std::string document,
	Protocol protocol,
	unsigned short port)
{
	if (protocol != Protocol::NO_PROTOCOL)
		m_protocol = protocol;
	else
		throw CUrlParsingError("Invalid protocol");
	if (std::regex_match(domain, std::regex(DOMAIN_PATTERN)))
		m_domain = domain;
	else
		throw CUrlParsingError("Invalid protocol");
	m_port = port;
	if (document.length() == 0 || document[0] != '/')
	{
		document = "/" + document;
	}
	if (std::regex_match(document, std::regex(DOCUMEN_PATTERN + QUERY_STRING)))
		m_document = document;
	else
		throw CUrlParsingError("Invalid document");
}

std::string CHttpUrl::GetURL() const
{
	if (m_port == static_cast<unsigned int>(m_protocol))
	{
		return m_protocol + "://" + m_domain + m_document;
	}
	else
	{
		return m_protocol + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
	}
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

std::string CHttpUrl::ToString() const
{
	std::string result;
	result += GetURL() + "\n";
	result += ProtocolToString(GetProtocol()) + "\n";
	result += GetDomain() + "\n";
	result += std::to_string(GetPort()) + "\n";
	result += GetDocument() + "\n";
	return result;
}