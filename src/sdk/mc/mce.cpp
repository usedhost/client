#include "mce.hpp"
#include "../signatures.hpp"

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
    uint64_t hash = HashedString(mPath).getHash();
    mPathHash = hash;
    mFullHash = hash ^ (uint64_t)mFileSystem;
}

namespace cg { class ImageBuffer; }

uint32_t cg::ImageDescription::getStrideFromFormat(const mce::TextureFormat format)
{
    switch (format) {
    case mce::TextureFormat::R32G32B32A32_FLOAT:
        return 16;

    case mce::TextureFormat::R8G8B8A8_UNORM:
        return 4;

    case mce::TextureFormat::A8_UNORM:
        return 1;
    }
}

namespace mce {
    Blob::Blob() : mBlob(nullptr, Deleter()), mSize(0) {}

    Blob::Blob(const iterator data, const size_type size)
        : mBlob(new value_type[size], defaultDeleter), mSize(size)
    {
        std::copy(data, data + size, mBlob.get());
    }

    Blob::Blob(const Blob& other)
        : mSize(other.mSize), mBlob(nullptr, Deleter(other.mBlob.get_deleter().getDeleteFunc()))
    {
        if (other.mBlob) {
            value_type* newData = new value_type[other.mSize];
            std::copy(other.mBlob.get(), other.mBlob.get() + other.mSize, newData);
            mBlob.reset(newData);
        }
    }

    Blob::size_type Blob::size() const
    {
        return mSize;
    }

    void Blob::defaultDeleter(iterator data)
    {
        delete[] data;
    }

    mce::MaterialPtr* MaterialPtr::createMaterial(const HashedString& name) {
        uintptr_t addr = reinterpret_cast<uintptr_t>(selaura::signatures::mce_rendermaterialgroup_ui.resolve());
        uintptr_t offseted_addr = selaura::offset_from_sig(addr, 3);
        return selaura::call_virtual<mce::MaterialPtr*, const HashedString&>(reinterpret_cast<void*>(offseted_addr), 1, name);
    };

    BedrockTexture& TextureGroup::uploadTexture(const ResourceLocation& resource, cg::ImageBuffer imageBuffer) {
        static auto func = reinterpret_cast<selaura::signatures::mce_texturegroup_uploadtexture_t>(selaura::signatures::mce_texturegroup_uploadtexture.resolve());
        return func(resource, imageBuffer);
    };
};

void MeshHelpers::renderMeshImmediately(void* a1, void* a2, void* a3) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(selaura::signatures::meshhelpers_rendermeshimmediately.resolve());

    static auto func = reinterpret_cast<selaura::signatures::meshhelpers_rendermeshimmediately_t>(selaura::offset_from_sig(addr, 1));
    char pad[0x58]{};
    func(a1, a2, a3, pad);
}