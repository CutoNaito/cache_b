#include "httpresponse.h"

using namespace std;

HttpResponse::HttpResponse(string _url, string _host_header, string _body, int _code)
{
	this->url = _url;
	this->host_header = _host_header;
	this->body = _body;
	this->code = _code;

	this->key = generate_key();
}

string HttpResponse::generate_key()
{
	return (this->host_header + "|" + this->url);
}

string HttpResponse::get_key()
{
	return this->key;
}

string HttpResponse::get_body()
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
