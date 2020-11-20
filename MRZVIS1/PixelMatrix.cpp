//
// Created by nicolas on 04/10/2020.
//

#include "PixelMatrix.h"
#include "PixelRGB.h"

PixelMatrix::PixelMatrix(PixelMatrix&& moveMatrix) noexcept :
        HEIGHT(moveMatrix.HEIGHT),
        WIDTH(moveMatrix.WIDTH){
    pixels = std::move(moveMatrix.pixels);
    header = std::move(moveMatrix.header);
    offset = std::move(moveMatrix.offset);
    if(moveMatrix.isCompletlyCreated()){
        isComplete = true;
    }else{
        isComplete = false;
        curHeight = moveMatrix.curHeight;
        curWidth = moveMatrix.curWidth;
    }
}

uint32_t PixelMatrix::getHeight() const {
    return HEIGHT;
}

uint32_t PixelMatrix::getWidth() const {
    return WIDTH;
}

void PixelMatrix::addPixel(const PixelRGB& pixel) {
    if(curWidth >= WIDTH){
        curWidth = 0;
        curHeight++;
    }
    if(curHeight >= HEIGHT){
        isComplete = true;
        return;
    }
    pixels[curHeight][curWidth] = pixel;
    curWidth++;
}

bool PixelMatrix::isCompletlyCreated() const noexcept {
    return isComplete;
}
