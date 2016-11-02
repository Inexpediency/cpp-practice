#include "stdafx.h"
#include "../ParseUrl/parse_url_utils.h"

void CheckUrlParse(const std::string & url, Protocol correctProtocol, int correctPort, const std::string & correctHost, const std::string & correctDocument)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	BOOST_CHECK(ParseURL(url, protocol, port, host, document));
	BOOST_CHECK(protocol == correctProtocol);
	BOOST_CHECK_EQUAL(host, correctHost);
	BOOST_CHECK_EQUAL(port, correctPort);
	BOOST_CHECK_EQUAL(document, correctDocument);
}

BOOST_AUTO_TEST_SUITE(Is_url_tests)
	
	BOOST_AUTO_TEST_CASE(Protocol_host_port_document_test)
	{
		BOOST_CHECK(IsUrl("http://mysite.com:80/doc/pic"));
		BOOST_CHECK(IsUrl("http://www.mysite.com:80/doc/pic"));
		BOOST_CHECK(IsUrl("https://mysite.com:80/doc/pic.png"));
		BOOST_CHECK(IsUrl("https://www.mysite.com:80/doc/pic.png"));
		BOOST_CHECK(IsUrl("ftp://mysite.com:80/doc/pic.png"));
		BOOST_CHECK(IsUrl("ftp://www.mysite.com:80/doc/pic.png"));
		BOOST_CHECK(!IsUrl("hhh://mysite.com:80/doc/pic.png"));
		BOOST_CHECK(!IsUrl("http://mysite.com:80/doc/pic.png/"));
		BOOST_CHECK(!IsUrl("http://mysite.:80/doc/pic.png/"));
		BOOST_CHECK(!IsUrl("http://.com:80/doc/pic.png/"));
	}
	
	BOOST_AUTO_TEST_CASE(Protocol_host_document_test)
	{
		BOOST_CHECK(IsUrl("http://mysite.com/doc/pic.png"));
		BOOST_CHECK(IsUrl("https://mysite.com/doc/pic.png"));
		BOOST_CHECK(IsUrl("ftp://mysite.com/doc/pic.png"));
		BOOST_CHECK(!IsUrl("hhh://mysite.com/doc/pic.png"));
		BOOST_CHECK(!IsUrl("http://mysite.com/doc/pic.png/"));
		BOOST_CHECK(!IsUrl("http://mysite./doc/pic.png/"));
		BOOST_CHECK(!IsUrl("http://.com/doc/pic.png/"));
	}

	BOOST_AUTO_TEST_CASE(Protocol_host_test)
	{
		BOOST_CHECK(IsUrl("http://mysite.com"));
		BOOST_CHECK(IsUrl("https://mysite.com"));
		BOOST_CHECK(IsUrl("ftp://mysite.com"));
		BOOST_CHECK(!IsUrl("hhh://mysite.com"));
		BOOST_CHECK(!IsUrl("http://mysite.com/"));
		BOOST_CHECK(!IsUrl("http://mysite."));
		BOOST_CHECK(!IsUrl("http://.com"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Parse_url_tests)
	BOOST_AUTO_TEST_CASE(Protocol_host_port_document_test)
	{
		CheckUrlParse("http://mysite.com:90/doc/pic", Protocol::HTTP, 90, "mysite.com", "/doc/pic");
		CheckUrlParse("http://www.mysite.com:90/doc/pic", Protocol::HTTP, 90, "www.mysite.com", "/doc/pic");
	}
	BOOST_AUTO_TEST_CASE(Protocol_host_port_test)
	{
		CheckUrlParse("http://mysite.com:90", Protocol::HTTP, 90, "mysite.com", "");
	}
	BOOST_AUTO_TEST_CASE(Protocol_host_document_test)
	{
		CheckUrlParse("http://mysite.com/doc/pic", Protocol::HTTP, 80, "mysite.com", "/doc/pic");
	}
	BOOST_AUTO_TEST_CASE(Protocol_host_test)
	{
		CheckUrlParse("https://mysite.com", Protocol::HTTPS, 443, "mysite.com", "");
	}
BOOST_AUTO_TEST_SUITE_END()
