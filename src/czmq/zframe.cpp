#include "../../include/czmq/zframe.h"

void ZFrame::__construct(Php::Parameters &param) {
	set_handle(zframe_new(NULL, 0), true, "zframe");
}

Php::Value ZFrame::__toString() {
    char *frame = zframe_strdup (zframe_handle());
	Php::Value buffer = frame;
	free(frame);
	return buffer.stringValue();
}

void ZFrame::dump() {
	zframe_print(zframe_handle(), NULL);
}