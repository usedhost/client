#include "selaura.hpp"

std::unique_ptr<selaura::instance> selaura::inst;

void selaura::init() {
	inst = std::make_unique<selaura::instance>();
	inst->start();
}
