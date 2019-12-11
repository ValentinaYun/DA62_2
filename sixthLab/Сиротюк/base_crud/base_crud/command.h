#pragma once

#include <cinttypes>
#include <string>

/*!
 * \brief Namespace that used for containing all api frontend command control
 * \version 0.1
 */
namespace					control {
/*!
* \brief Enumarator that contain all command id`s to be used with the "command" and the "command_register"
* \version 0.1
*/
enum						command_id : uint32_t {
	create					= 0,
	read					,
	update					,
	destroy					,
	exit					,

	invalid					= uint32_t(-1),
};

/*!
* \brief Structure that contain command name and indexes
* \details Command register enumerate all commands, that can be used inside api
* \version 0.1
*/
struct						command {
	constexpr inline		command(const char* name, const command_id token) : name(name), token(token) {}

	const char*				name;
	const command_id		token;

};

/*!
* \brief Class that used for all API`s command parsing and execution
* \todo Callback to move all command executions inside "command_controller" class instead of execting command outside by delegating a job by tokens.
* \version 0.1
*/
class						command_controller {
public:
	inline					command_controller() {}

	std::string				get_command_data(command_id& id, const std::string &serialized_cmd, const uint32_t offset);
};
};