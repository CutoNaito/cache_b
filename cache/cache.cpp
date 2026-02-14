#include <iostream>
#include "httpresponse.h"
#include "cacheresponse.h"

using namespace std;

// int main(void)
// {
// 	HttpResponse a = HttpResponse("testa", "testh", "test body", 200);
// 	HttpResponse b = HttpResponse("testb", "testh", "test body", 200);
// 	HttpResponse c = HttpResponse("testc", "testh", "test body", 200);
// 
// 	std::string key_a = a.get_key();
// 	std::string key_b = b.get_key();
// 	std::string key_c = c.get_key();
// 
// 	CacheResponse cache = CacheResponse(1);
// 	cache.insert(std::move(a));
// 	cache.insert(std::move(b));
// 
// 	HttpResponse *res;
// 	if (cache.lookup(key_a, &res)) {
// 		cout << "true\n";
// 		cout << (res)->get_key() + "\n";
// 	}
// 
// 	cache.insert(std::move(c));
// 	if (cache.lookup(key_b, &res)) {
// 		cout << "true\n";
// 		cout << (res)->get_key() + "\n";
// 	}
// }
