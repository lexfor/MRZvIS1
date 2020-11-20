//
// Created by nicolas on 03/10/2020.
//

#include <fstream>
#include <iostream>
#include "PictureStream.h"
#include "PixelMatrix.h"
#include <iterator>

PixelMatrix PictureStream::ReadFromBMP(const std::string &Path) {
    static constexpr size_t HEADER_SIZE = 54;
    std::ifstream bmp(Path, std::ios::binary);

    std::vector<char> header(HEADER_SIZE);
    if (bmp.is_open()) {
        bmp.read(header.data(), header.size());
    } else {
        throw std::ifstream::failure("No open File provided");
    }
    auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
    auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
    auto width = *reinterpret_cast<uint32_t *>(&header[18]);
    auto height = abs(*reinterpret_cast<int32_t *>(&header[22]));
    auto bitPerPixel = *reinterpret_cast<uint16_t *>(&header[28]);

    if (bitPerPixel != 32)throw std::ifstream::failure("incorrect bit count");

    PixelMatrix result(height, width);
    result.header = header;

    std::vector<char> image(dataOffset - HEADER_SIZE);
    bmp.read(image.data(), image.size());
    result.offset = image;

    image.resize(width * height * 4);
    bmp.read(image.data(), image.size());
    bmp.close();

    for (size_t i = --fileSize - dataOffset; i > 3; i -= 4) {
        uint8_t blue = image[i];
        uint8_t green = image[i - 1];
        uint8_t red = image[i - 2];
        result.addPixel(PixelRGB(red, green, blue));
    }

    return result;
}

void PictureStream::WriteToBMP(const PixelMatrix &pixelMatrix) {
    std::ofstream bmp("D:\\picture.bmp", std::ios::binary);
    if (bmp.is_open()) {
        bmp.write(pixelMatrix.header.data(), pixelMatrix.header.size());
        bmp.write(pixelMatrix.offset.data(), pixelMatrix.offset.size());
        constexpr uint8_t blank = 255;
        constexpr uint8_t blank2 = 0;
        for (auto row = pixelMatrix.pixels.rbegin(); row != pixelMatrix.pixels.rend(); row++) {
            for (auto col = (*row).rbegin(); col != (*row).rend(); col++) {
                bmp.write((char *) &(*col).Blue, 1);
                bmp.write((char *) &(*col).Green, 1);
                bmp.write((char *) &(*col).Red, 1);
                bmp.write((char*)  &blank, 1);
            }
        }
    }else{
        throw std::ios::failure("Cant open file to write");
    }
    bmp.close();
}
