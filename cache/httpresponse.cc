#include "httpresponse.h"

HttpResponse::HttpResponse(std::string _key, std::string _url, std::string _host_header, std::string _body, int _code)
{
	this->key = _key;
	this->url = _url;
	this->host_header = _host_header;
	this->body = _body;
	this->code = _code;
}

std::string HttpResponse::get_key()
{
	return this->key;
}

std::string HttpResponse::get_body()
{
	return this->body;
}

int HttpResponse::get_code()
{
	return this->code;
}

bool HttpResponse::is_valid()
{
	return !this->key.empty();
}
