#pragma once
#include "client/common/IMinecraftApp.hpp"

class IMinecraftGame : public IMinecraftApp {
public:
    virtual void initialize(int, char**) = 0;
    virtual ~IMinecraftGame() = default;
    virtual void update() = 0;
};
