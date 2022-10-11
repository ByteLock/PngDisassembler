#include "./headers/disassembler.h"

char pngtrail[5] = ".png";

void print_header() {
    printf("╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╭╮\n");
    printf("╱╱╱╱╱╱╱╱╱╱╱╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃┃╱┃┃\n");
    printf("╭━━┳━╮╭━━╮╭━╯┣┳━━┳━━┳━━┳━━┳━━┳╮╭┫╰━┫┃╭━━┳━╮\n");
    printf(" ┃╭╮┃╭╮┫╭╮┃┃╭╮┣┫━━┫╭╮┃━━┫━━┫┃━┫╰╯┃╭╮┃┃┃┃━┫╭╯\n");
    printf("┃╰╯┃┃┃┃╰╯┃┃╰╯┃┣━━┃╭╮┣━━┣━━┃┃━┫┃┃┃╰╯┃╰┫┃━┫┃\n");
    printf("┃╭━┻╯╰┻━╮┃╰━━┻┻━━┻╯╰┻━━┻━━┻━━┻┻┻┻━━┻━┻━━┻╯\n");
    printf("┃┃╱╱╱╱╭━╯┃\n");
    printf("╰╯╱╱╱╱╰━━╯\n");
}
void print_options() {
    printf("1. Extract Chunk\n");
    printf("2. Extract Disassemble\n");
    printf("3. Extract Chunks to File\n");
    printf("4. Exit\n");
}

void handleBaseDisassemble() {
    printf("\x1b[23H\x1b[2J");
    printf("please enter the file name: \n");
    printf("(make sure it is in the same folder)\x1b[A\x1b[23;29H");
    std::string input;
    std::cin >> input;
    printf("\n");
    char ichars[sizeof(input)];
    for(int i = 0; i < sizeof(input); i++) {
        ichars[i] = input[i];
    }
    Disassembler::disassemble(ichars);
}

void handleExtractDisassemble() {
    printf("\x1b[23H\x1b[2J");
    printf("please enter the file name: \n");
    printf("(make sure it is in the same folder)\x1b[A\x1b[23;29H");
    std::string input;
    std::cin >> input;
    printf("\n");
    char ichars[sizeof(input)];
    for(int i = 0; i < sizeof(input); i++) {
        ichars[i] = input[i];
    }
    Disassembler::disassemble_output(ichars);
}

int main() {
    while(true) {
        // Setup Display
        printf("\x1b[2H]\x1b[2J");
        print_header();
        print_options();
        char input[2];
        std::cin >> input;

        // Handle Input
        if(strcmp(input, "1") == 0) {
        }
        if(strcmp(input, "2") == 0) {
            handleBaseDisassemble();
        }
        if(strcmp(input, "3") == 0) {
            handleExtractDisassemble();
        }
        if(strcmp(input, "4") == 0) {
            exit(1);
        }
    }
}