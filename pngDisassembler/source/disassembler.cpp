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
    printf("\ntotal Size: %d\n", fileSize);
    
    // Create a vectr that takes vector<char>s
    std::vector<std::vector<char>  > chunks;
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
        printf("chunk Size: %d\n", chunkSize);
        printf("chunk Type: %s\n", chunk.type);

        // Create a new byte buffer with the chunkSize + 4 bytes (the size of the crc)
        // char * buffer[chunkSize + 4];
        char * heap_ptr = nullptr;
        if(chunkSize + 4 != 4) {
            printf("allocating memory page..\n");
            heap_ptr = (char *)malloc(chunkSize + 4); 
            printf("done.. ");
        }
        printf("str cmp val: %d\n", strcmp(chunk.type, "tEXt"));
        printf("first 10 bytes: ");
        char x[1];
        std::cin >> x;
        
        if(chunkSize != 0 && chunkSize > 10) {
            for(int i = 0; i < 10; i++) {
            printf("%u ", &heap_ptr[i]);
            }
        }
        printf("\n");
        
        
        printf("heap address: %x\n", &heap_ptr);
        
        // Read the bytes to the buffer, then append them to the data vector
        printf("projected read position: %d\n", (int)f.tellg()+ chunkSize + 4);
        printf("reading chunk...\n");
        f.read((char *)heap_ptr, chunkSize + 4);
        // for(int i = 0; i < sizeof(heap_ptr); i++) {
        //     data.push_back(heap_ptr[i]);
        // }
        printf("done!\n");
        // Push the data vector to the chunk vector
        //chunks.push_back(data);
        printf("chunk read position: %d\n", (int)f.tellg());
        printf("------------------------------\n");
        z++;
    }
    printf("chunk vectors size %lu\n", sizeof(chunks));
    printf("total chunks read: %d\n", z);
    return 1;
}