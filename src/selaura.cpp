#include "selaura.hpp"

std::unique_ptr<selaura::instance> selaura::inst;
static std::once_flag flag;

void selaura::init() {
	std::call_once(flag, []() {
		inst = std::make_unique<selaura::instance>();
		inst->start();
	});
}
