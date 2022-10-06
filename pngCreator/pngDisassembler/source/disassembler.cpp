#include "../headers/structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Color Type Rules
 * Color: 0 | Allowed Bit Depths: 1, 2, 4, 8, 16
 * Color: 2 | Allowed Bit Depths: 8, 16
 * Color: 3 | Allowed Bit Depths: 1, 2, 4, 8
 * Color: 4 | Allowed Bit Depths: 8, 16
 * Color: 6 | Allowed Bit Depths: 8, 16
 */
int COLOR_TYPE_RULES[5][6] = {
    {0, 1, 2, 4, 8, 16},
    {2, 8, 16},
    {3, 1, 2, 4, 8},
    {4, 8, 16},
    {6, 8, 16}
};

int disassemble(const char file[], char * fileBuffer) {
    std::ifstream f(file, std::ios::out | std::ios::binary);
    if(!f.is_open() || !f) {
        printf("could not find file..\n");
        return 0;
    } else {
        printf("found file.. %s\n", file);
    }

    // Determine file size
    f.seekg(0, f.end);
    int fileSize = f.tellg();
    f.seekg(0, f.beg);

    // Read file signature
    _FileSig fileSignature;
    f.read((char *)&fileSignature, sizeof(_FileSig));
    printf("read sig: ");
    for(auto c : fileSignature.signature) {
        printf("%d ", c);
    }
    printf("\n");

    std::vector<std::vector<char>  > chunks;
    while (!(f.tellg() == fileSize))
    {
        std::vector<char> byteVector;
        _Chunk chunk;
        f.read((char *)&chunk, sizeof(chunk));
        int chunkSize = ntohl(chunk.length);
        printf("Chunk Length: %d\n", chunkSize);
        printf("Chunk Type: %s\n", chunk.type);
        unsigned char buffer[chunkSize + 4];
        f.read((char *)&buffer, chunkSize + 4);
        for(auto c : buffer) {
            byteVector.push_back(c);
        }
        chunks.push_back(byteVector);
        printf("------------------------------\n");
    }
    printf("v size %lu", sizeof(chunks));
    return 1;
}