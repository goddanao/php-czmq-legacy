#include "../include/zchunk.h"

void ZChunk::__construct(Php::Parameters &param) {
	set_handle(zchunk_new(NULL,0), true, "zchunk");
}

void ZChunk::dump() {
	zchunk_print(zchunk_handle());
}

Php::Class<ZChunk> ZChunk::php_register() {
	Php::Class<ZChunk> o("ZChunk");
	o.method("__construct", &ZChunk::__construct);
	o.method("dump", &ZChunk::dump);
	return o;
}