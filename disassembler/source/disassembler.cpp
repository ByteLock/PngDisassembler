#include "../headers/structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <format>

namespace Disassembler {    

    // output file 
    std::ofstream o("disassembled.txt", std::ios::binary);

    void writeOutput(char * heap_ptr, int size) {
        for(int i = 0; i < size; i++) {
                unsigned int hexch = (unsigned int)(unsigned char)heap_ptr[i];
                o << std::setw(2) << std::setfill('0') << std::hex << hexch << " ";
                printf("%d ", i);
                if(i % 10 <= 0 && i != 0) {
                    o.write(nl, 2);
                    printf("\n");
                }
        }
    }

    /**
     * @brief Disassemble a PNG file and print out file specific information
     * 
     * @param file the file name
     * @return the status code
     */
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
     * @brief Disassembles and generates an output file
     * 
     * @param file the file (png) name
     * @return the status code 
     */
    int disassemble_output(const char file[]) {
        // input file
        std::ifstream f(file, std::ios::out | std::ios::binary);
        
        if(!f.is_open() || !f && !o.is_open() || !o) {
            printf("one or more files couldn't be find or created..\n");
            return 0;
        } else {
            printf("found file.. %s\n", file);
        }

        // Determine file size
        f.seekg(0, f.end);
        int fileSize = f.tellg();
        f.seekg(0, f.beg);

        // Read file signature
        char * sig_ptr = (char *)malloc(sizeof(_FileSig));
        f.read(sig_ptr, sizeof(_FileSig));
        o.write(ls, 32);
        o << "File Signature";
        o.write(nl, 2);
        writeOutput(sig_ptr, sizeof(_FileSig));
        free(sig_ptr);
        o << "\n";
        

        int z = 0;
        printf("------------------------------\n");
        // Read the file until we reach the end
        while (!(f.tellg() >= fileSize))
        {   
            int x;
            std::cin >> x;
            printf("current read pos: %d\n", (int)f.tellg());
            // create a chunk struct and memory page
            _Chunk chunk;

            // Read the next 8 bytes (hopefully the chunk header)
            f.read((char *)&chunk, sizeof(chunk));

            // go back the size of a chunk header
            f.seekg((int)f.tellg() - (sizeof(_Chunk)));

            // Go from reverse byte order to host byte order (png files have the bytes written in reverse)
            int chunkSize = ntohl(chunk.length);
            printf("data size: %d\n", chunkSize);

            // Output file formatting 
            char * ldata = ("%c", chunk.type);
            o.write(ls, 32);
            o.write(ldata, sizeof(ldata));
            o.write(nl, 2);

            // Create a heap_ptr with the size of the chunk
            chunkSize = chunkSize + sizeof(_Chunk) + sizeof(_CRC);
            printf("read size: %d\n", chunkSize);
            char * heap_ptr = (char *)malloc(chunkSize); 

            // Read the actual bytes from the input png file
            f.read((char *)heap_ptr, chunkSize);
            printf("writing memory page to output... \n");

            // Write out the hex value to the output file
            // for(int i = 0; i < chunkSize; i++) {
            //     unsigned int hexch = (unsigned int)(unsigned char)heap_ptr[i];
            //     o << std::setw(2) << std::setfill('0') << std::hex << hexch << " ";
            //     if(i % 10 == 0) {
            //         o.write(nl, 2);
            //     }
            // }
            writeOutput(heap_ptr, chunkSize);
            o << "\n";
            printf("done.. \n");

            // Print out our current position
            printf("chunk read position: %d\n", (int)f.tellg());
            printf("------------------------------\n");
            z++;
            o.flush();
        }
        o.close();
        printf("total chunks read: %d\n", z);
        int x;
        std::cin >> x;
        return 1;
    }

}