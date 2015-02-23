#include "../../include/czmq/zcert.h"

void ZCert::__construct(Php::Parameters &param) {
	if(param.size() == 0)
		set_handle(zcert_new (), true, "zcert");
	else
		set_handle(zcert_load(param[0].stringValue().c_str()), true, "zcert");
}

Php::Value ZCert::get_public_key() {
	Php::Value result;
	char *buffer  = result.reserve(32);
	byte *pubcert = zcert_public_key(zcert_handle());
	memcpy(buffer, pubcert, 32);
	return result;
}

Php::Value ZCert::get_secret_key() {
	Php::Value result;
	char *buffer  = result.reserve(32);
	byte *pubcert = zcert_secret_key(zcert_handle());
	memcpy(buffer, pubcert, 32);
	return result;
}

Php::Value ZCert::get_public_key_txt() {
	return zcert_public_txt(zcert_handle());
}

Php::Value ZCert::get_secret_key_txt() {
	return zcert_secret_txt(zcert_handle());
}

void ZCert::set_meta(Php::Parameters &param) {
	 zcert_set_meta(zcert_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str());
}

Php::Value ZCert::get_meta(Php::Parameters &param) {
	 return zcert_meta(zcert_handle(), param[0].stringValue().c_str());
}

Php::Value ZCert::get_meta_keys() {
	Php::Value result;
	zlist_t *meta_keys = zcert_meta_keys(zcert_handle());
	if(!meta_keys)
		return Php::Array();
	char *meta_key = (char *) zlist_first(meta_keys);
	int result_idx = 0;
	while (meta_key) {
		result[result_idx++] = meta_key;
		meta_key = (char *) zlist_next(meta_keys);
	}
	zlist_destroy(&meta_keys);
	return result;
}

void ZCert::save(Php::Parameters &param) {
	zcert_save(zcert_handle(), param[0].stringValue().c_str());
}

void ZCert::save_public(Php::Parameters &param) {
	zcert_save_public(zcert_handle(), param[0].stringValue().c_str());
}

void ZCert::save_secret(Php::Parameters &param) {
	zcert_save_secret(zcert_handle(), param[0].stringValue().c_str());
}

void ZCert::apply(Php::Parameters &param) {
	if(param[0].isObject()) {
		ZHandle *zhandle = dynamic_cast<ZHandle*>(param[0].implementation());
		if(zhandle && zhandle->get_socket())
			zcert_apply(zcert_handle(), zhandle->get_socket());
	}
}

void ZCert::dump() {
	zcert_print(zcert_handle());
}

void ZCert::__clone() {
	set_handle(zcert_dup(zcert_handle()), true, "zcert");
}

int ZCert::__compare(const ZCert &that) const {
	return (int) (zcert_eq(zcert_handle(), that.zcert_handle()) ? 0 : -1);
}