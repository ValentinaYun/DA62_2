#pragma once

#include "record.h"

/*!
* \brief Wrapper above the "record_pull"
* \details Wrapper above the "record_pull" used as API frontend and interface
* \version FINAL
*/
class							crud_controller {
public:
	inline						crud_controller() {}

public:
	agnostic::record_handler	crt_record();
	agnostic::record_handler	get_record(const uint32_t idx);
	agnostic::record_handler	get_record(const char *data);
	void						set_record(const app::record record);

	void						dlt_record(const agnostic::record_handler handler);
	void						dlt_record(const uint32_t idx);
};