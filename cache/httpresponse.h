#pragma once

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
		HttpResponse(std::string _key, std::string _url, std::string _host_header, std::string _body, int _code);
		std::string get_key();
		std::string get_body();
		int get_code();
		bool is_valid();
};
