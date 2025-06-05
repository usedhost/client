#pragma once
#include <cstddef>
#include <cstdint>
#include <variant>
#include <memory>

#include "HashedString.hpp"

enum class ResourceFileSystem : int {
    UserPackage,
    AppPackage,
    Raw,
    RawPersistent,
    SettingsDir,
    ExternalDir,
    ServerPackage,
    DataDir,
    UserDir,
    ScreenshotsDir,
    StoreCache,
    Invalid
};

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
namespace cg { class ImageBuffer; }

namespace mce {
    enum class PrimitiveMode : uint8_t {
        None,
        QuadList,
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip
    };

    enum class TextureFormat : unsigned int {
        UNKNOWN_TEXTURE_FORMAT = 0x0,
        R32G32B32A32_FLOAT = 0x2,
        R16G16B16A16_FLOAT = 0xA,
        R16G16B16A16_UNORM = 0xB,
        R32G32_FLOAT = 0x10,
        R10G10B10A2_UNORM = 0x18,
        R11G11B10_FLOAT = 0x1A,
        R8G8B8A8_UNORM = 0x1C,
        R8G8B8A8_UNORM_SRGB = 0x1D,
        R16G16_FLOAT = 0x22,
        R16G16_UNORM = 0x23,
        R16G16_UINT = 0x24,
        R16G16_SNORM = 0x25,
        D32_FLOAT = 0x28,
        R32_FLOAT = 0x29,
        R32_UINT = 0x2A,
        R24G8_TYPELESS = 0x2C,
        D24_UNORM_S8_UINT = 0x2D,
        R24_UNORM_X8_TYPELESS = 0x2E,
        R8G8_UNORM = 0x31,
        R8G8_SNORM = 0x33,
        R16_FLOAT = 0x36,
        D16_UNORM = 0x37,
        R8_UNORM = 0x3D,
        R8_UINT = 0x3E,
        A8_UNORM = 0x41,
        BC3_UNORM = 0x4D,
        R5G6B5_UNORM = 0x55,
        R5G5B5A1_UNORM = 0x56,
        B8G8R8A8_UNORM = 0x57,
        B8G8R8A8_UNORM_SRGB = 0x5B,
        BC7_UNORM = 0x62,
        R4G4B4A4_UNORM = 0x73,
        S8_UINT = 0x74,
        ASTC_4x4 = 0x75,
        ASTC_5x4 = 0x76,
        ASTC_5x5 = 0x77,
        ASTC_6x5 = 0x78,
        ASTC_6x6 = 0x79,
        ASTC_8x5 = 0x7A,
        ASTC_8x6 = 0x7B,
        ASTC_8x8 = 0x7C,
        ASTC_10x5 = 0x7D,
        ASTC_10x6 = 0x7E,
        ASTC_10x8 = 0x7F,
        ASTC_10x10 = 0x80,
        ASTC_12x10 = 0x81,
        ASTC_12x12 = 0x82,
        ASTC_4x4_SRGB = 0x83,
        ASTC_5x4_SRGB = 0x84,
        ASTC_5x5_SRGB = 0x85,
        ASTC_6x5_SRGB = 0x86,
        ASTC_6x6_SRGB = 0x87,
        ASTC_8x5_SRGB = 0x88,
        ASTC_8x6_SRGB = 0x89,
        ASTC_8x8_SRGB = 0x8A,
        ASTC_10x5_SRGB = 0x8B,
        ASTC_10x6_SRGB = 0x8C,
        ASTC_10x8_SRGB = 0x8D,
        ASTC_10x10_SRGB = 0x8E,
        ASTC_12x10_SRGB = 0x8F,
        ASTC_12x12_SRGB = 0x90,
        R8G8B8_UNORM = 0x91,
    };

    class Blob {
    public:
        typedef std::size_t size_type;
        typedef uint8_t value_type;
        typedef mce::Blob::value_type* iterator;
        typedef void (*delete_function)(value_type*);

        struct Deleter {
            mce::Blob::delete_function m_func;

            Deleter() : m_func(nullptr) {}
            Deleter(delete_function func) : m_func(func) {}

            void operator()(value_type* ptr) const {
                if (m_func) {
                    m_func(ptr);
                }
                else {
                    delete[] ptr;
                }
            }

            delete_function getDeleteFunc() const {
                return m_func;
            }
        };

        typedef std::unique_ptr<unsigned char[], Deleter> pointer_type;

    private:
        pointer_type mBlob;
        size_type mSize;

    public:
        Blob();
        Blob(const iterator data, const size_type size);
        Blob(const Blob& other);

        size_type size() const;

        static void defaultDeleter(iterator data);
    };

    struct BedrockTexture {};
    struct TexturePtr {};
    struct TextureGroup {
        BedrockTexture& uploadTexture(const ResourceLocation& resource, cg::ImageBuffer imageBuffer);
    };

    struct MaterialPtr {
        static mce::MaterialPtr* createMaterial(const HashedString& name);
    };
};

namespace cg {
    enum class ColorSpace : unsigned char {
        Unknown,
        sRGB,
        Linear
    };
    enum class ImageType : unsigned char {
        Texture2D,
        Cubemap,
        Texture3D,
        TextureCube,
    };
    struct ImageDescription {
        uint32_t mWidth;
        uint32_t mHeight;
        mce::TextureFormat mTextureFormat;
        cg::ColorSpace mColorSpace;
        cg::ImageType mImageType;
        uint32_t mArraySize;

        ImageDescription(uint32_t width, uint32_t height, mce::TextureFormat format, cg::ColorSpace colorSpace, cg::ImageType imageType, uint32_t arraySize)
            : mWidth(width), mHeight(height), mTextureFormat(format), mColorSpace(colorSpace), mImageType(imageType), mArraySize(arraySize) {
        }

        static uint32_t getStrideFromFormat(const mce::TextureFormat format);
    };

    class ImageBuffer {
    public:
        mce::Blob mStorage;
        cg::ImageDescription mImageDescription;

        ImageBuffer(mce::Blob&& blob, cg::ImageDescription&& imageDescription)
            : mStorage(std::move(blob)), mImageDescription(std::move(imageDescription)) {
        }

        ImageBuffer(const ImageBuffer& other)
            : mStorage(other.mStorage), mImageDescription(other.mImageDescription) {
        }

        __declspec(noinline) bool isValid() const {
            size_t blobSize = mStorage.size();
            mce::TextureFormat format = mImageDescription.mTextureFormat;

            if ((unsigned int)format - 117 > 0x1B) {
                int v6 = 0;

                if (mImageDescription.mWidth != 0 && mImageDescription.mHeight != 0) {
                    v6 = mImageDescription.mWidth * mImageDescription.mHeight * cg::ImageDescription::getStrideFromFormat(format);
                }

                int v8 = 6;
                if (mImageDescription.mImageType != cg::ImageType::Cubemap) {
                    v8 = mImageDescription.mArraySize;
                }

                return blobSize == v6 * v8;
            }
        }
    };
};


struct MeshHelpers {
    static void renderMeshImmediately(void* a1, void* a2, void* a3);
};