#pragma once
#include <cstddef>
#include <memory>

namespace mce {
    class ClientTexture {};
    class ServerTexture {};
}

struct BedrockTextureData {
    mce::ClientTexture mClientTexture;
};

class BedrockTexture {
public:
    std::shared_ptr<BedrockTextureData> mBedrockTextureData;
};