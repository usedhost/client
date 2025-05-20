#include "selaura.hpp"

static std::once_flag flag;
HMODULE selaura::hmodule = nullptr;

void selaura::init() {
	selaura::instance::get().start();
}
