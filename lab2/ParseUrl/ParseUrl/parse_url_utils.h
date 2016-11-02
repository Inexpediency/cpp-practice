#pragma once
#include "stdafx.h"

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21,
	NO_PROTOCOL,
};

Protocol StringToProtocol(const std::string & protocol);
std::string ProtocolToString(Protocol protocol);
std::string ToLowCase(std::string str);
bool IsUrl(const std::string & url);
bool ParseURL(const std::string & url, Protocol &  protocol, int & port, std::string & host, std::string & document);