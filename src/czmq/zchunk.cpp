#include "../../include/czmq/zchunk.h"

void ZChunk::__construct(Php::Parameters &param) {
	zchunk_t *chunk = zchunk_new(NULL,0);
	if(chunk)
		set_handle(chunk, true, "zchunk");
	else
		throw Php::Exception("Can't create ZChunk");
}

void ZChunk::dump() {
	zchunk_print(zchunk_handle());
}