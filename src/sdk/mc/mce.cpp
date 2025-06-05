#include "mce.hpp"
#include "../signatures.hpp"

namespace mce {
    mce::MaterialPtr* MaterialPtr::createMaterial(const HashedString& name) {
        uintptr_t addr = reinterpret_cast<uintptr_t>(selaura::signatures::mce_rendermaterialgroup_ui.resolve());
        uintptr_t offseted_addr = selaura::offset_from_sig(addr, 3);
        return selaura::call_virtual<mce::MaterialPtr*, const HashedString&>(reinterpret_cast<void*>(offseted_addr), 1, name);
    };
};

void MeshHelpers::renderMeshImmediately(void* a1, void* a2, void* a3) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(selaura::signatures::meshhelpers_rendermeshimmediately.resolve());

    static auto func = reinterpret_cast<selaura::signatures::meshhelpers_rendermeshimmediately_t>(selaura::offset_from_sig(addr, 1));
    char pad[0x58]{};
    func(a1, a2, a3, pad);
}