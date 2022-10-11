#include "../headers/structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Disassembler {    

    int disassemble(const char file[]) {
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
                printf("allocating memory page..\n");
                 char * heap_ptr = (char *)malloc(chunkSize); 
                printf("done.. \n");

                printf("projected read position: %d\n", (int)f.tellg()+ chunkSize + 4);
                printf("reading chunk...\n");
                f.read((char *)heap_ptr, chunkSize);
                printf("done!\n");
                if(chunkSize < 100) {
                    printf("raw hex bytes: ");
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
        int x;
        std::cin >> x;
        return 1;
    }
    
    /**
     * @brief Disassembles and outputs a file
     * 
     * @param file the file (png) name
     * @return the status code of the operation
     */
    int disassemble_output(const char file[]) {
        // input file
        std::ifstream f(file, std::ios::out | std::ios::binary);
        
        // output file 
        std::ofstream o("disassembled.txt", std::ios::hex | std::ios::binary);

        // Ensure that our files are open
        if(!f.is_open() || !f && !o.is_open() || !o) {
            printf("one or more files couldn't be find or created..\n");
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

            // We will only read the chunk size if it is not 0
            if(chunkSize != 0) {
                // Create a heap_ptr with the size of the chunk
                printf("allocating memory page..\n");
                char * heap_ptr = (char *)malloc(chunkSize); 
                printf("done.. \n");

                // Print out the heap address
                printf("heap address: %x\n", &heap_ptr);

                // Print out the projected read position after the bytes
                printf("projected read position: %d\n", (int)f.tellg()+ chunkSize + 4);

                // Read the actual bytes from the input png file
                printf("reading chunk...\n");
                f.read((char *)heap_ptr, chunkSize);

                // Write out the hex value to the output file
                o.write(heap_ptr, chunkSize);
                printf("done!\n");

                // Print out the preview hex bytes (cannot be more than 100 bytes)
                if(chunkSize < 100) {
                    printf("raw hex bytes: ");
                    for(int i = 0; i < chunkSize; i++) {
                            printf("%x ", heap_ptr[i]);
                    }          
                }
                printf("\n");
            }

            // Create a buffer for the crc outside of the chunk because EVERY chunk has a CRC besides the file signature
            char crc[4];
            printf("crc: ");
            for(int i = 0; i < sizeof(crc); i++) {
                printf("%x ", crc[i]);
            }
            printf("\n");

            // Read the last 4 bytes which are the CRC
            f.read((char *)&crc, sizeof(crc));

            // Print out our current position
            printf("chunk read position: %d\n", (int)f.tellg());


            printf("------------------------------\n");
            o.write("\n------------------------------\n", 32);
            z++;
        }
        printf("total chunks read: %d\n", z);
        int x;
        std::cin >> x;
        return 1;
    }
}