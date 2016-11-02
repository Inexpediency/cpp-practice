#include "stdafx.h"
#include "parse_url_utils.h"


const std::string PROTOCOL_PATTERN = "((https)|(http)|(ftp))";
const std::string HOST_PATTERN = "(((\\w|-)+\\.)+\\w+)";
const std::string PORT_PATTERN = "(:(\\d)+)?";
const std::string DOCUMEN_PATTERN = "((/(\\w|-)+)+(/((\\w|-)+\\.\\w+))?)?";
const std::string QUERY_STRING = "(\\?.*)?";
const std::string URL_PATTERN = PROTOCOL_PATTERN + "://" + HOST_PATTERN + PORT_PATTERN + DOCUMEN_PATTERN + QUERY_STRING;

Protocol StringToProtocol(const std::string & protocol)
{
	if (protocol == "http")
		return Protocol::HTTP;
	else if (protocol == "https")
		return Protocol::HTTPS;
	else if (protocol == "ftp")
		return Protocol::FTP;
	else return Protocol::NO_PROTOCOL;
}

std::string ProtocolToString(Protocol protocol)
{
	if (protocol == Protocol::HTTP)
		return "http";
	else if (protocol == Protocol::HTTPS)
		return "https";
	else if (protocol == Protocol::FTP)
		return "ftp";
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

bool IsUrl(const std::string & url)
{
	auto correctUrl = std::regex(URL_PATTERN);
	return std::regex_match(url, correctUrl);
}

Protocol CutProtocol(std::string & url)
{
	std::string protocol = url.substr(0, url.find("://"));
	url.erase(0, protocol.length() + 3);
	return StringToProtocol(protocol);
}

std::string CutHost(std::string & url)
{
	auto hostEndPos = url.find(":");
	hostEndPos = hostEndPos == std::string::npos ? url.find("/") : hostEndPos;
	hostEndPos = hostEndPos == std::string::npos ? url.length() : hostEndPos;
	std::string host = url.substr(0, hostEndPos);
	url.erase(0, hostEndPos);
	return host;
}

int CutPort(std::string & url, Protocol protocol)
{
	auto portEndPos = url.find("/");
	portEndPos = portEndPos == std::string::npos ? url.length() : portEndPos;
	std::string port = url.substr(0, portEndPos);
	url.erase(0, port.length());
	return port != "" ? stoi(port) : static_cast<int>(protocol);
}

bool ParseURL(const std::string & url, Protocol &  protocol, int & port, std::string & host, std::string & document)
{
	std::string tempUrl = ToLowCase(url);
	if (!IsUrl(url))
	{
		return false;
	}
	protocol = CutProtocol(tempUrl);
	host = CutHost(tempUrl);
	if (tempUrl[0] == ':')
	{
		tempUrl.erase(0, 1);
	}
	port = CutPort(tempUrl, protocol);
	document = tempUrl;
	return true;
}