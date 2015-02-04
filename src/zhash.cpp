#include "../include/zhash.h"

void ZHash::__construct(Php::Parameters &param) {
	set_handle(zhash_new(), true, "zhash");
}

Php::Class<ZHash> ZHash::php_register() {
	Php::Class<ZHash> o("ZHash");
	o.method("__construct", &ZHash::__construct);
	return o;
}