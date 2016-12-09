#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

int main()
{
	std::string urlStr;
	while (std::getline(std::cin, urlStr))
	{
		try
		{
			CHttpUrl url(urlStr);
			std::cout << url.ToString() << std::endl;
		}
		catch (CUrlParsingError & err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	return 0;
}

