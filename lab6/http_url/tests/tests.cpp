#include "stdafx.h"
#include "../http_url/HttpUrl.h"
#include "../http_url/UrlParsingError.h"

BOOST_AUTO_TEST_SUITE(HttpUrl)

	BOOST_AUTO_TEST_SUITE(can_be_created_by_single_string)
		BOOST_AUTO_TEST_CASE(with_document_and_port)
		{
			CHttpUrl url("http://mysite.com:100/doc/pic.com");
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/doc/pic.com");
		}
		BOOST_AUTO_TEST_CASE(with_document)
		{
			CHttpUrl url("https://mysite.com/doc/pic");
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 443);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/doc/pic");
		}
		BOOST_AUTO_TEST_CASE(with_port)
		{
			CHttpUrl url("https://mysite.com:100");
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		}
		BOOST_AUTO_TEST_CASE(without_port_and_document)
		{
			CHttpUrl url("https://mysite.com");
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 443);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(throw_exeption_when_in_string)
		BOOST_AUTO_TEST_CASE(incorrect_protocol)
		{
			BOOST_CHECK_THROW(CHttpUrl("noProtocol://mysite.com"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(incorrect_domain_name)
		{
			BOOST_CHECK_THROW(CHttpUrl("HTTP://"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("HTTP://.ñom"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("HTTP://ñom."), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(incorrect_port)
		{
			BOOST_CHECK_THROW(CHttpUrl("https://mysite.com:"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://mysite.com:/doc/pic.png"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://mysite.com:90doc/pic.png"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(incorrect_document)
		{
			BOOST_CHECK_THROW(CHttpUrl("https://mysite.com:80//pic.png"), CUrlParsingError);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(can_be_created_with_parametr_like)
		BOOST_AUTO_TEST_CASE(domain_name_document_protocol_port)
		{
			CHttpUrl url("mysite.com", "/doc/pic.com", Protocol::HTTPS, 100);
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/doc/pic.com");
		}
		BOOST_AUTO_TEST_CASE(domain_name_document_protocol)
		{
			CHttpUrl url("mysite.com", "/doc/pic.com", Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/doc/pic.com");
		}
		BOOST_AUTO_TEST_CASE(domain_name_document)
		{
			CHttpUrl url("mysite.com", "/doc/pic.com", Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetDomain(), "mysite.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/doc/pic.com");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(throw_exeption_when_in_parametr)
		BOOST_AUTO_TEST_CASE(incorrect_protocol)
		{
			BOOST_CHECK_THROW(CHttpUrl("mysite.com", "/doc/pic.com", Protocol::NO_PROTOCOL), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(incorrect_domain_name)
		{
			BOOST_CHECK_THROW(CHttpUrl(".com", "/doc/pic.com", Protocol::HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("com.", "/doc/pic.com", Protocol::HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("", "/doc/pic.com", Protocol::HTTP), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(incorrect_document)
		{
			BOOST_CHECK_THROW(CHttpUrl("com.", "//", Protocol::HTTP), CUrlParsingError);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()