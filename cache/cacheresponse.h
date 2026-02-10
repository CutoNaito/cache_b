#ifndef CACHERESPONSE_H
#define CACHERESPONSE_H

#include "ring.h"
#include <unordered_map>

class CacheResponse {
	private:
		RingBuffer ring;
		std::unordered_map<std::string, size_t> map;
	
	public:
		CacheResponse(int _cap);
		void insert(HttpResponse&& res);
		bool lookup(std::string key, HttpResponse** res);
		std::unordered_map<std::string, size_t> get_map();
		RingBuffer get_ring();
};

#endif
