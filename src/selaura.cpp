#include "selaura.hpp"

static std::once_flag flag;

void selaura::init() {
	std::call_once(flag, []() {
		selaura::instance::get().start();
	});
}
