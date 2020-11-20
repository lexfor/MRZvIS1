//
// Created by nicolas on 04/10/2020.
//

#ifndef NEURALONE_PIXELMATRIX_H
#define NEURALONE_PIXELMATRIX_H


#include <cstdint>
#include <vector>
#include "PixelRGB.h"

class PixelMatrix {
public:
    PixelMatrix(PixelMatrix&& moveMatrix)noexcept;
    uint32_t getHeight()const;
    uint32_t getWidth()const;
    bool isCompletlyCreated()const noexcept;
private:
    PixelMatrix(const uint32_t height, const uint32_t width) :
            HEIGHT(height),
            WIDTH(width){
        pixels.resize(HEIGHT, std::vector<PixelRGB>(WIDTH));
    }
    void addPixel(const PixelRGB& pixel);
    std::vector<char> header;
    std::vector<char> offset;
    std::vector<std::vector<PixelRGB>> pixels;
    const uint32_t HEIGHT;
    const uint32_t WIDTH;
    uint32_t curHeight = 0;
    uint32_t curWidth = 0;
    bool isComplete = false;
    friend class PictureStream;
};


#endif //NEURALONE_PIXELMATRIX_H
