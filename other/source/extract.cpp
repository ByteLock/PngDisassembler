#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

struct chunk {
    unsigned int length;
    unsigned char typeCode[4];
};

struct pngSig {
    unsigned char signature[8];
};

struct idhr {
    unsigned int width;
    unsigned int height;
    unsigned char bit_depth;
    unsigned char color_type;
    unsigned char compression_method;
    unsigned char filter_method;
    unsigned char interlace_method;
};  

// first col is color, and the following are the supported bit depths
int COLOR_TYPE_RULES[5][6] = {
    {0, 1, 2, 4, 8, 16},
    {2, 8, 16},
    {3, 1, 2, 4, 8},
    {4, 8, 16},
    {6, 8, 16}
};

/**
 * @brief Checks the COLOR_TYPE_RULES and verifies a color has the appropriate bit channel
 * 
 * @param depth the bit depth of the png
 * @param color the color of the png
 * @return 0 - Fails | 1 - Success
 */
int verifyChannelColors(int depth, int color) {
    for(int i = 0; i < 5; i++) {
        if(COLOR_TYPE_RULES[i][0] == color) {
            for(int j = 0; j < 6; j++) {
                if(COLOR_TYPE_RULES[i][j] == depth) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * @brief Extract Ihdr
 * 
 * @param fileName The png that you want to extract the idhr from
 * @param buffer The buffer that you want the ihdr data to be written to
 * @return The status | 0 = Fail | 1 = Success
 */
int extractIhdr(const char fileName[], char * buffer) {
    
    // open a file with (ifstream)
    std::ifstream f(fileName, std::ios::out | std::ios::binary);
    if(!f) {
        std::cout << "couldn't open file" << std::endl;
        return 0;
    }

    pngSig sig;
    // read the file sig
    f.read((char *)&(sig), sizeof(pngSig));
    // print the decimal file sig
    printf("File Signature (decimal): ");
    for(int i = 0; i < sizeof(pngSig); i++) {
        printf("%d ", sig.signature[i]);
    }
    printf("\n");
    unsigned int chunkSize;
    unsigned char chunkType[4];
    f.read((char *)&chunkSize, sizeof(chunkSize));
    f.read((char *)&chunkType, sizeof(chunkType));
    idhr pngIhdr;
    f.read((char *)&pngIhdr, sizeof(idhr));
    
    // some very interesting things going on here:
    /**
     * @brief Because M1 macs uses a reverse order to store multi-byte values in (in nerverse network order)
     * we have to convert it to a host byte order
     * @url: https://linux.die.net/man/3/ntohl
     */
    pngIhdr.height = ntohl(pngIhdr.height);
    pngIhdr.width = ntohl(pngIhdr.width);
    chunkSize = ntohl(chunkSize);

    printf("Chunk Size: %d\n", chunkSize);
    printf("Chunk Type: %s\n\n", chunkType);
    printf("Width: %d pixels\n", pngIhdr.height);
    printf("Height: %d pixels\n", pngIhdr.width);
    printf("Bit Depth: %d bits per channel\n", pngIhdr.bit_depth);
    printf("Color Type: %d\n", pngIhdr.color_type);
    printf("Compression Method: %d\n", pngIhdr.compression_method);
    printf("Filter Method: %d\n", pngIhdr.filter_method);
    printf("Interlace Method: %d\n", pngIhdr.interlace_method);
    printf("\n");
    printf("Bit-Depth and Color Verification: %d\n", verifyChannelColors(pngIhdr.bit_depth, pngIhdr.color_type));

    memcpy(buffer, &pngIhdr, sizeof(pngIhdr));

    // read the crc
    unsigned char buffer3[1];
    f.read((char *)&buffer3, sizeof(buffer3));

    chunk nChunk;
    f.read((char *)&chunkSize, sizeof(chunkSize));
    f.read((char *)&chunkType, sizeof(chunkType));
    chunkSize = ntohl(chunkSize);
    printf("\nChunk Size: %d\n", chunkSize);
    printf("Chunk Name: %s\n", chunkType);
    f.seekg(chunkSize + 45);
    f.read((char *)&chunkSize, sizeof(chunkSize));
    f.read((char *)&chunkType, sizeof(chunkType));
    printf("\nChunk Size: %d\n", chunkSize);
    printf("Chunk Name: %s\n", chunkType);
    return 1;
}