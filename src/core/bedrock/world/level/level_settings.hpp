#pragma once

#include "level_seed.hpp"

namespace selaura::bedrock {
    class LevelSettings {
    public:
        [[nodiscard]] LevelSeed64 getSeed() const
        {
            return seed_;
        }

        void setRandomSeed(LevelSeed64 seed)
        {
            seed_ = seed;
        }

    private:
        LevelSeed64 seed_;
    };
};