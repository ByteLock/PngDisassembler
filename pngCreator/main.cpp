#include <iostream>
#include <fstream>
#include <string>
#include "./headers/generate.h"
#include "./headers/extract.h"
#include "./external/base64/base64.h"

/**
 * @brief Read a PNG
 * 
 * @param fileName The name of the file you want to read
 * @param data The data buffer you want the data to be written to
 * @return The status | 0 - Fail | 1 - Success
 */
int readPng(const char fileName[], char * data) {
    std::ifstream f(fileName, std::ios::out | std::ios::binary);
    if(!f) {
        std::cout << "couldn't open file" << std::endl;
        return 0;
    }

    // go to the end of the file and get the position (size)
    f.seekg(0, f.end);
    int fileSize = f.tellg();
    // go back to the beginning of the file
    f.seekg(0, f.beg);

    // create the byte buffer for the image (pref a size LARGER than the image so.. you.. dont.. lose... data...)
    char buffer[fileSize];
    
    // write to the byte buffer and then print out the bytes as you read them
    for(int i = 0; i < fileSize; i++) {
        // read a char
        f.read(&buffer[i], 1);
        data[i] = buffer[i];
        
        // print the byte we read at the buffer index that we wrote at 
        // std::cout << data[i] << std::endl;
    }

    std::cout << "File size: " << fileSize << " bytes" << std::endl;

    return 1;
}

int getFileSize(const char fileName[]) {
    std::ifstream f(fileName, std::ios::out | std::ios::binary);
    if(!f) {
        std::cout << "couldn't open file" << std::endl;
        return 0;
    }

    // go to the end of the file and get the position (size)
    f.seekg(0, f.end);
    int fileSize = f.tellg();
    return fileSize;
}

int main() {
    char filePath[] = "water.png";
    char idhrBuffer[sizeof(idhr)];
    extractIhdr(filePath, idhrBuffer);
    printf("\nIhdr Buffer Returned: ");
    for(int i = 0; i < sizeof(idhrBuffer); i++) {
        printf("%X ", idhrBuffer[i]);
    }
    idhr returned;
    memcpy(&returned, &idhrBuffer, sizeof(idhrBuffer));
    printf("\nBuffer wrote to: %x from: %x", &returned, &idhrBuffer);
    printf("\nbit depth: %d\n", returned.bit_depth);

    // zero the bits
    // for(int i = 0; i < sizeof(idhrBuffer); i++) {
    //     *((char *) &idhrBuffer[i]) = *((char *)&idhrBuffer[i]) & ~idhrBuffer[i];
    // }
    &idhrBuffer = &idhrBuffer & ~*((char *)idhrBuffer);

    printf("\nIhdr Buffer Returned: ");
    for(int i = 0; i < sizeof(idhrBuffer); i++) {
        printf("%X ", idhrBuffer[i]);
    }
    memcpy(&returned, &idhrBuffer, sizeof(idhrBuffer));
    printf("\nBuffer wrote to: %x from: %x", &returned, &idhrBuffer);
    printf("\nbit depth: %d\n", returned.bit_depth);
    return 0;
}

