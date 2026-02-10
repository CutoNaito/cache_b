#include "cacheresponse.h"
#include "httpresponse.h"
#include "ring.h"
#include <iostream>
#include <unordered_map>

CacheResponse::CacheResponse(int _cap) : ring(_cap)
{
}

void CacheResponse::insert(HttpResponse&& res)
{
	int slot = ring.get_index();

	HttpResponse* ex = ring.peek(slot);
	if (ex && ex->is_valid())
		map.erase(ex->get_key());

	ring.append_ow(std::move(res));

	HttpResponse* in = ring.peek(slot);
	map[in->get_key()] = slot;

	std::cout << "INSERT key=" << in->get_key()
          << " slot=" << slot
          << " map_size=" << map.size()
          << "\n";
}

bool CacheResponse::lookup(std::string key, HttpResponse** out)
{
	auto entry = map.find(key);
	if (entry == map.end()) {
		return false;
	}

	int slot = entry->second;
	
	*out = ring.peek(slot);
	if (!(*out) || !(*out)->is_valid()) {
		return false;
	}

	return true;
}

std::unordered_map<std::string, size_t> CacheResponse::get_map()
{
	return map;
}

RingBuffer CacheResponse::get_ring()
{
	return ring;
}
