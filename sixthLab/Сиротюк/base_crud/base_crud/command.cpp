#include "command.h"

#include <assert.h>
#include <vector>
#include <string>

static const std::vector<control::command> command_register = {
	{"create",				control::create			},
	{"read",				control::read			},
	{"update",				control::update			},
	{"delete",				control::destroy		},
	{"exit",				control::exit			}
};


namespace				control {
std::string				command_controller::get_command_data(command_id& id, const std::string &serialized_cmd, const uint32_t offset) {
	id					= control::invalid;

	if (offset > 0) {
		for (command cmd : command_register) {
			if (serialized_cmd.find(std::string("/#") + std::string(cmd.name)) == 0) {
				id			= cmd.token;
				break;
			}
		}

		if (id != control::invalid && id != control::exit) {
			int8_t res = (int8_t)serialized_cmd.find(" ");
			if (res != -1) {
				res			= res + 1;
				std::string cutted = serialized_cmd.substr(res, std::string::npos);

				if (offset == 1) {
					int8_t arg_res = cutted.find("/#");
					return	(cutted.substr(0, arg_res - 1));
				} else {
					res = (int8_t)cutted.find(" ");
					if (res != -1) {
						res = res + 1;
						return cutted.substr(res + 2, std::string::npos);
					}
				}
			}
		}
	}

	return				(std::string());
}
};