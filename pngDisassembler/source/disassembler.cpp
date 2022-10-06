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
    for(int i = 0; i < sizeof(fileSignature.signature); i++) {
        printf("%d ", fileSignature.signature[i]);
    }
    printf("\n");
    
    // Create a vectr that takes vector<char>s
    std::vector<std::vector<char>  > chunks;
    int z = 0;
    printf("------------------------------\n");

    // Read the file until we reach the end
    while (!(f.tellg() == fileSize))
    {   
        // The data chunk (found in headers/structs.h)
        _Chunk chunk;
        
        // The data vector that contains the data bytes of the current chunk
        std::vector<char> data;

        // Read the data chunk
        f.read((char *)&chunk, sizeof(chunk));

        // Go from reverse byte order to host byte order (png files have the bytes written in reverse)
        int chunkSize = ntohl(chunk.length);

        // Print outputs
        printf("Chunk Length: %d\n", chunkSize);
        printf("Chunk Type: %s\n", chunk.type);

        // Create a new byte buffer with the chunkSize + 4 bytes (the size of the crc)
        unsigned char buffer[chunkSize + 4];

        // Read the bytes to the buffer, then append them to the data vector
        f.read((char *)&buffer, chunkSize + 4);
        for(int i = 0; i < sizeof(buffer); i++) {
            data.push_back(buffer[i]);
        }

        // Push the data vector to the chunk vector
        chunks.push_back(data);
        printf("------------------------------\n");
        z++;
    }
    printf("chunk vectors size %lu\n", sizeof(chunks));
    printf("total chunks read: %d\n", z);
    return 1;
}