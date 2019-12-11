#pragma once

#include <vector>
#include <mutex>
#include <assert.h>

#include "record.h"

namespace									app {
/*!
* \brief Class that used to wrap all interactions with record register.
* \details Class contain record register that contain all records. That singleton does not allow to get real instance of the any record, but allow to 
*  obtain a handler to some record to interact with data, contained inside record. This decision was maked due to the platform agnostic ideology and also
*  this is a good oportunity to creat our own allocation pull in order to obtain memory allocation speed up in future.
* \todo Memory pool and memory allocation. Thread safety for handlers and generation non-blocking algorithm based on atomics memory bariers
* \warning "record_pull" operations thread-safe by themselfs, but operations with handlers are not. So be careful when update something directly throw handler. 
*  You should not deleta some data, when someone hold another handler to that recoed
* \version 0.1
*/
class										record_pull {
public:
	//multithread safe during to c++11 standard
	static record_pull&						instance() {
		static record_pull					inst;
		return								(inst);
	}

	agnostic::record_handler				crt_record() {
		std::lock_guard<std::mutex>			lock(_dumb_lock);

		instance()._records.emplace_back	(nullptr);
		const uint32_t size					= instance()._records.size();
		assert								(size > 0);

		const uint32_t idx					= size - 1;
		assert								(idx < size && idx >= 0);

		app::record& record					= instance()._records[idx];
		return								(agnostic::record_handler(idx, record));
	}
	
	agnostic::record_handler				get_record(const uint32_t idx) {
		std::lock_guard<std::mutex>			lock(_dumb_lock);

		app::record &record					= instance()._records[idx];
		return								(agnostic::record_handler(idx, record));
	}

	agnostic::record_handler				get_record(const const char *str) {
		std::lock_guard<std::mutex>			lock(_dumb_lock);

		std::vector<app::record> &records	= instance()._records;
		const uint32_t size					= records.size();
		for (uint32_t idx = 0; idx < size; ++idx) {
			if (!records[idx].data) {
				continue;
			}

			if (strcmp(str, records[idx].data) == 0) {
				return						agnostic::record_handler(idx, records[idx]);
			}
		}
	}
	
	void									set_record(const app::record &record) {
		std::lock_guard<std::mutex>			lock(_dumb_lock);

#ifndef NDEBUG 
		const uint32_t original_size		= _records.size();
#endif NDEBUG

		_records.push_back					(record);

#ifndef NDEBUG
		const uint32_t modified_size		= _records.size();
#endif NDEBUG

		assert								(original_size > modified_size && original_size == (modified_size + 1));
	}

	void									dlt_record(const uint32_t idx) {
		assert								(idx >= 0);

		_records.erase						(std::next(_records.begin(), idx));
	}

private:
	static const uint32_t base_capacity		= 100000;
	inline									record_pull() {
		_records.reserve					(base_capacity);
	}

	inline									~record_pull() {
		for (app::record &x : _records) {
			if (x.data != nullptr) {
				delete x.data;
			}
		}
	}

	//singleton instance
											record_pull(const record_pull &rhs) = delete;
			record_pull						operator=(const record_pull &rhs) = delete;

	//it is more cleary to use generetion free algorithms
	std::mutex								_dumb_lock;
	std::vector<app::record>				_records;
};
}