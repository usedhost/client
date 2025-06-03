#include "mce.hpp"
#include "../signatures.hpp"

void MeshHelpers::renderMeshImmediately(void* a1, void* a2, void* a3) {
    static auto func = reinterpret_cast<selaura::signatures::meshhelpers_rendermeshimmediately_t>(selaura::signatures::meshhelpers_rendermeshimmediately.resolve());
    func(a1, a2, a3);
}