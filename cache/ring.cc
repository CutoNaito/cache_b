#include <stdexcept>
#include <utility>

#include "httpresponse.h"
#include "ring.h"

using namespace std;

RingBuffer::RingBuffer(int _capacity)
{
	if (_capacity < 0)
		throw invalid_argument("Invalid capacity");

	this->capacity = _capacity + 1;
	this->head = 0;
	this->tail = 0;
	buffer.resize(capacity);
}

void RingBuffer::append(HttpResponse entry)
{
	if ((tail + 1) % capacity == head)
		throw overflow_error("Buffer is full");

	buffer[tail] = entry;
	tail = (tail + 1) % capacity;
}

void RingBuffer::append_ow(HttpResponse&& entry)
{
	buffer[tail] = std::move(entry);
	tail = (tail + 1) % capacity;

	if (tail == head)
		head = (head + 1) % capacity;
}

void RingBuffer::pop()
{
	if (head == tail)
		throw underflow_error("Buffer is empty");

	head = (head + 1) % capacity;
}

HttpResponse RingBuffer::get_head()
{
	if (head == tail)
		throw underflow_error("Buffer is empty");

	return buffer[head];
}

HttpResponse RingBuffer::get_tail()
{
	if (head == tail)
		throw underflow_error("Buffer is empty");

	return buffer[tail];
}

int RingBuffer::get_index()
{
	return tail;
}

HttpResponse* RingBuffer::peek(int index)
{
	if (index < 0 || index >= capacity)
		return nullptr;
	return &buffer[index];
}

int RingBuffer::size()
{
	if (tail >= head)
		return (tail - head);
	return (capacity - (head - tail));
}
