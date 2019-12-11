#include "command.h"
#include "control.h"
#include <iostream>
#include <assert.h>

static control::command_controller command_controller;
static crud_controller			input_controller;

agnostic::record_handler get_handler(const std::string &data, const control::command_id id) {

	switch (id) {
	case control::create:
		return					(input_controller.crt_record());

	case control::update:
	case control::invalid:
	case control::destroy:
	case control::read:
		return					(input_controller.get_record(data.c_str()));
	}
}

int	main(int argc, char **argv) {
	control::command_id		id = control::invalid;
	while (id != control::exit) {
		std::string			input;
		std::getline		(std::cin, input);
		if (input.empty() || std::cin.fail()) {
			std::cin.clear();
			continue;
		}


		std::string name	 = command_controller.get_command_data(id, input, 1);
		if (!name.empty()) {
			agnostic::record_handler handler = get_handler(name, id);
			switch (id) {
				case control::create:
					handler.set_data(name.c_str());
					break;

				case control::update:
					handler.set_data(command_controller.get_command_data(id, input, 2).c_str());
					break;

				case control::destroy:
					input_controller.dlt_record(handler);
					break;

				case control::invalid:
				default:
					assert	(false);
			}
		}
	}

	return					(0);
}