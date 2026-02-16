#pragma once

#include <string>
#include <vector>

#include "httpresponse.h"

class RingBuffer {
	private:
		std::vector<HttpResponse> buffer;
		int head;
		int tail;
		int capacity;

	public:
		RingBuffer(int _capacity);
		void append(HttpResponse entry);
		void append_ow(HttpResponse&& entry);
		void pop();
		HttpResponse get_head();
		HttpResponse get_tail();
		int get_index();
		HttpResponse* peek(int index);
		int size();
};
