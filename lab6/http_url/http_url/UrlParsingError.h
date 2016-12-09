#pragma once
#include <stdexcept>
#include <string>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(const std::string & url) : std::invalid_argument(url) {};
	explicit CUrlParsingError::CUrlParsingError(const char * url) : std::invalid_argument(url) {};
};