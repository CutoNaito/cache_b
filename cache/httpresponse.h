#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>

class HttpResponse {
	private:
		std::string key;
		std::string url;
		std::string host_header;
		std::string body;
		int code;

	public:
		HttpResponse() : code(0) {}	
		HttpResponse(std::string _url, std::string _host_header, std::string _body, int _code);
		std::string generate_key();
		std::string get_key();
		bool is_valid();
};

#endif
