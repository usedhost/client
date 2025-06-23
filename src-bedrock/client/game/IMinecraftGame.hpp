#pragma once
#include "client/common/IMinecraftApp.hpp"
#include "deps/core/utility/EnableNonOwnerReferences.hpp"

class IMinecraftGame : public IMinecraftApp, public Bedrock::EnableNonOwnerReferences {
public:
    virtual void initialize(int, char**) = 0;
    virtual ~IMinecraftGame() = default;
    virtual void update() = 0;
};
