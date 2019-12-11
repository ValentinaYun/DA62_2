#pragma once

#include <cinttypes>
#include <cstring>

/*!
 * \brief Namespace that used for containing all unstable and mutable realization
 * \details Used to star all classes and structures that have unstable realization or platfrom dependant. Like data types that contained inside the low-level singletones
 * \version 0.1
 */
namespace				app {

/*!
 * \brief Structure that used to typedef and hold real view of the user record
 * \details Structure containt pointer to char string. In our alpha (0.1) version we assume that data will be stored alongside with spacial characters
 * that will tell how frontend must formate and represantate data on viewport.
 * \warning Only "record_handler" interface allowed to interact with record through. Direct interactions with record struct can broke up everything.
 * \version 0.1
 */
struct					record {
	inline				record(char *data) : data(data) {}

	char				*data;
};
}

/*!
 * \brief Namespace that used for containing all platform agnostic realization
 * \version 0.1
 */
namespace				agnostic {

/*!
 * \brief Structure that used to wrap platform dependant record realization
 * \details Structure containt the adress of record and it index in the global record table "record_pull". Thread unsafe.
 * \warning Only this interface allowed to interact with record through. Direct interactions with record struct can broke up everything.
 * \version 0.1
 */
struct					record_handler {
	inline				record_handler(const uint32_t id, app::record& record) : _id(id), _record(record) {}

	inline const char*	get_data() const {
		return			_record.data;
	}
	
	inline void			set_data(const char *data) {
		delete			_record.data;
		_record.data	= _strdup(data);
	}
	
	inline uint32_t		get_id() const {
		return			_id;
	}

private:
	const uint32_t		_id;
	app::record&		_record;
};
};