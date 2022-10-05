#include <iostream>

int main() {

    int total = 0;
    int arr[] = {1, 2, 3, 4, 5, 6};
    for(int i = 0; i < sizeof(arr); i++) {
        printf("%i", arr[i]);
        total += arr[i];
    }
    printf("%i", total);

    return 0;
}