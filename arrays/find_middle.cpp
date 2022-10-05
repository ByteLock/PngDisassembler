#include <iostream>
#include "./find_middle.h"

int find(int arr[]) {
    printf("arr size: %i\n", sizeof(arr));
    printf("mod: %i\n", sizeof(arr) % 2);
    for(int i = 0; i < (sizeof(arr) / 2) - 1; i++) {
        printf("%i\n", arr[i]);
    }
}

int main() {
    int intarr[] = {1, 2, 3, 4, 5};
    find(intarr);
}