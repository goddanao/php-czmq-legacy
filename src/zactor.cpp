#include "../include/zactor.h"

void ZActor::set_verbose (Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
}
