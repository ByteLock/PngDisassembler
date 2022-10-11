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

    printf("current pos: %d\n", (int)f.tellg());
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
    printf("\ntotal Size: %d\n", fileSize);
    
    int z = 0;
    printf("------------------------------\n");
    // Read the file until we reach the end
    while (!(f.tellg() == fileSize))
    {   
        // The data chunk (found in headers/structs.h)
        _Chunk chunk;

        printf("chunk read position: %d\n", (int)f.tellg());
        
        // Read the data chunk
        f.read((char *)&chunk, sizeof(chunk));

        // Go from reverse byte order to host byte order (png files have the bytes written in reverse)
        int chunkSize = ntohl(chunk.length);

        // Print outputs
        printf("chunk size: %d\n", chunkSize);
        printf("chunk type: %s\n", chunk.type);
    
        if(chunkSize != 0) {
            // Create a new byte buffer with the chunkSize + 4 bytes (the size of the crc)
            // char * buffer[chunkSize + 4];
            char * heap_ptr = nullptr;
            if(chunkSize + 4 != 4) {
                printf("allocating memory page..\n");
                heap_ptr = (char *)malloc(chunkSize); 
                printf("done.. \n");
            }

            // Read the bytes to the buffer, then append them to the data vector
            printf("projected read position: %d\n", (int)f.tellg()+ chunkSize + 4);
            printf("reading chunk...\n");
            f.read((char *)heap_ptr, chunkSize);
            printf("done!\n");
            if(chunkSize < 100) {
                printf("raw hex bytes: ");
                int x;
                std::cin >> x;
                if(chunkSize != 0) {
                    for(int i = 0; i < chunkSize; i++) {
                        printf("%x ", heap_ptr[i]);
                    }
                }           
            }
            printf("\n");
            printf("heap address: %x\n", &heap_ptr);
        }
        char crc[4];
        printf("crc: ");
        for(int i = 0; i < sizeof(crc); i++) {
            printf("%x ", crc[i]);
        }
        printf("\n");
        f.read((char *)&crc, sizeof(crc));
        printf("chunk read position: %d\n", (int)f.tellg());
        printf("------------------------------\n");
        z++;
    }
    printf("total chunks read: %d\n", z);
    return 1;
}