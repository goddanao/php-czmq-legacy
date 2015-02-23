#include "../../include/czmq/zframe.h"

void ZFrame::__construct(Php::Parameters &param) {
	set_handle(zframe_new(NULL, 0), true, "zframe");
}

Php::Value ZFrame::__toString() {
	Php::Value buffer;
	int _buffer_size = zframe_size(zframe_handle());
	buffer.reserve(_buffer_size);
	const char *_buffer_to = buffer.rawValue();
	byte *_buffer_from = zframe_data(zframe_handle());
	memcpy((void *) _buffer_to, _buffer_from, _buffer_size);
	return buffer;
}

void ZFrame::dump() {
	zframe_print(zframe_handle(), NULL);
}