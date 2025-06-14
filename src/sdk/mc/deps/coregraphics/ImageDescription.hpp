#pragma once
#include <cstdint>
#include "enums/ColorSpace.hpp"
#include "enums/TextureFormat.hpp"
#include "enums/ImageType.hpp"

namespace cg {
    struct ImageDescription {
        uint32_t mWidth;
        uint32_t mHeight;
        mce::TextureFormat mTextureFormat;
        cg::ColorSpace mColorSpace;
        cg::ImageType mImageType;
        uint32_t mArraySize;

        ImageDescription(uint32_t width, uint32_t height, mce::TextureFormat format, cg::ColorSpace colorSpace, cg::ImageType imageType, uint32_t arraySize) 
            : mWidth(width), mHeight(height), mTextureFormat(format), mColorSpace(colorSpace), mImageType(imageType), mArraySize(arraySize) {}

        static uint32_t getStrideFromFormat(const mce::TextureFormat format);
    };
};