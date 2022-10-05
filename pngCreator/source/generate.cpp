#include <iostream>
#include <fstream>

/**
 * @brief Create a Png object
 * 
 * @param fsig The file signature (usual same 8 bytes)
 * @param idhr The image's data header bytes
 * @param idata The image data bytes
 * @param iend The bytes of the end of the image file 
 * @return The status | 0 - Fail | 1 - Success
 */
int createPng(char fsig[], char idhr[], char idata[], char iend[]) {

    return 1;
}

/**
 * @brief Create a Png object
 * 
 * @param fileName The name of the new file you want to create
 * @param buffer The image's data buffer
 * @param fileSize The size of the image
 * @return The status | 0 - Fail | 1 - Success
 */
int createPng(const char fileName[], char buffer[], int fileSize) {
    std::ofstream f (fileName, std::ios::out | std::ios::binary);
    if(!f) {
        std::cout << "couldn't create file" << std::endl;
        return 0;
    }
    f.write(buffer, fileSize);
    return 1;
}

/**
 * @brief Generate a test PNG
 * 
 * @param fileName The name of the test png
 * @return The status | 0 - Fail | 1 - Success
 */
int generateTest(const char fileName[]) {
    std::ofstream f (fileName, std::ios::out | std::ios::binary);
    if(!f) {
        std::cout << "couldn't create file" << std::endl;
        return 0;
    }

    // file signature
    char fsig[8] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

    // the image header
    char ihdr[25] = {
        0x00, 0x00, 0x00, 
        0x0d, 0x49, 0x48, 
        0x44, 0x52, 0x00, 
        0x00, 0x00, 0x03, 
        0x00, 0x00, 0x00, 
        0x02, 0x08, 0x02, 
        0x00, 0x00, 0x00, 
        0x12, 0x16, 0xf1, 
        0x4d
    };

    // the image data
    char idat[256] = {
        0x00, 0x00, 0x00, 
        0x1f, 0x49, 0x44, 
        0x41, 0x54, 0x08, 
        0x1d, 0x01, 0x14, 
        0x00, 0xeb, 0xff, 
        0x00, 0xff, 0x00, 
        0x00, 0x00, 0xff, 
        0x00, 0x00, 0x00, 
        0xff, 0x00, 0x00, 
        0x00, 0x00, 0x80, 
        0x80, 0x80, 0xff, 
        0xff, 0xff, 0x3a, 
        0x61, 0x07, 0x7b, 
        0xcb, 0xca, 0x5c, 
        0x63
    };

    // the image trailer
    char iend[12] = {
        0x00, 0x00, 0x00, 
        0x00, 0x49, 0x45, 
        0x4e, 0x44, 0xae, 
        0x42, 0x60, 0x82
    };

    // write to the file
    f.write(fsig, sizeof(fsig));
    f.write(ihdr, sizeof(ihdr));
    f.write(idat, sizeof(idat));
    f.write(iend, sizeof(iend));

    return 1;
}