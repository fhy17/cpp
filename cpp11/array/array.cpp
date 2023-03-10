#include <iostream>
#include <string>
#include <stdio.h>

int main() {
    int arr[] = {0, 1};
    std::cout << "sizeof(arr): " << sizeof(arr) << std::endl;
    printf("arr \t%p\n", arr);
    printf("arr+1 \t%p\n", arr + 1);
    // printf("++arr \t%p\n", ++arr);
    auto p = &arr;
    printf("p+1 \t%p\n", p + 1);
    return 0;
}