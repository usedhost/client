#include "selaura.hpp"

std::unique_ptr<selaura::instance> selaura::inst;

void selaura::init() {
	std::terminate(); // if it crashes it works
	inst = std::make_unique<selaura::instance>();
	inst->start();
}
