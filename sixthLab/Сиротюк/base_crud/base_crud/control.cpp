#include "record_pull.h"
#include "control.h"


agnostic::record_handler	crud_controller::crt_record() {
	return					(app::record_pull::instance().crt_record());
}

agnostic::record_handler	crud_controller::get_record(const uint32_t idx) {
	return					(app::record_pull::instance().get_record(idx));
}

agnostic::record_handler	crud_controller::get_record(const char *data) {
	return					(app::record_pull::instance().get_record(data));
}

void						crud_controller::set_record(const app::record record) {
	app::record_pull::instance().set_record(record);
}

void						crud_controller::dlt_record(const agnostic::record_handler handler) {
	dlt_record				(handler.get_id());
}

void						crud_controller::dlt_record(const uint32_t idx) {
	app::record_pull::instance().dlt_record(idx);
}