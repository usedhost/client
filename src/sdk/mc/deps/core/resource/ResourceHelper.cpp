#include "ResourceHelper.hpp"
#include "ResourceUtil.hpp"
#include "../../../HashedString.hpp"

ResourceLocation::~ResourceLocation() {}

ResourceLocation::ResourceLocation() {
    mFileSystem = ResourceFileSystem::UserPackage;
    mPath = "";
    _computeHashes();
}

ResourceLocation::ResourceLocation(const std::string& path) {
    mFileSystem = ResourceFileSystem::UserPackage;
    mPath = path;
    _computeHashes();
}

ResourceLocation::ResourceLocation(const char* path) : ResourceLocation(std::string(path))
{
}

void ResourceLocation::_computeHashes()
{
    int64_t hash = HashedString(mPath).getHash();
    mPathHash = hash;
    mFullHash = hash ^ (uint64_t)mFileSystem;
}