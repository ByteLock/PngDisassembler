#define IHDR_CHUNK_LENGTH 13

/**
 * @brief The first 8 bytes of a png data chunk
 * unsigned int length (4 bytes)        | The length of the data within a chunk
 * unsigned char type[4] (4 bytes)      | The four letter type code | ex { IHDR, IDAT, IEND }
 */
struct _Chunk {
    unsigned int length;
    char type[4];
};

/**
 * @brief The first 8 bytes of a file
 * The initial 8 bytes of a png file should be: { 137 80 78 71 13 10 26 10 }
 * unsigned char signature[8]           | 8 byte character signature (read in string format)
 */
struct _FileSig {
    unsigned char signature[8];
};

struct _CRC {
    unsigned char crc[4];
};

/**
 * @brief The IHDR data chunk of a png file
 *  unsigned int width                  | Pixel width of an image
    unsigned int height                 | Pixel height of an image
    unsigned char bit_depth             | Bit depth of an image (check valid bit depths)
    unsigned char color_type            | Color types of an image (check valid color types)
    unsigned char compression_method    | Compression method used in the image
    unsigned char filter_method         | Filter method (if used) in the image
    unsigned char interlace_method      | Interlace method (if used) in the iamge
 */
struct _IHDR {
    unsigned int width;
    unsigned int height;
    char bit_depth;
    char color_type;
    char compression_method;
    char filter_method;
    char interlace_method;
};  

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

/**
 * @brief Output File Formatting Strings
 * 
 */
char * ls = "------------------------------ ";
char * nl = "\n";