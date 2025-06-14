#pragma once

namespace memwrap {
    struct single_mfp {
        uintptr_t ptr;
    };
    struct multi_mfp {
        uintptr_t ptr;
        int adj;
    };
    struct virtual_mfp {
        uintptr_t ptr;
        int adj;
        int vindex;
    };
    struct unknown_mfp {
        uintptr_t ptr;
        int adj;
        int vadj;
        int vindex;
    };


};