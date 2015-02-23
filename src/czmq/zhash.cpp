#include "../../include/czmq/zhash.h"

void ZHash::__construct(Php::Parameters &param) {
	set_handle(zhash_new(), true, "zhash");
}