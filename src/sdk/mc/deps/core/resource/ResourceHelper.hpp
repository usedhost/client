#pragma once
#include "ResourceUtil.hpp"
#include <string>

class ResourceLocation {
public:
    ResourceFileSystem mFileSystem;
    std::string mPath;
    uint64_t mPathHash;
    uint64_t mFullHash;

public:
    ~ResourceLocation();
    ResourceLocation();
    ResourceLocation(const std::string& path);
    ResourceLocation(const char* path);

private:
    void _computeHashes();
};

static_assert(offsetof(ResourceLocation, mPath) == 8);