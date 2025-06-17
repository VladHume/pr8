#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void generate_descending(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void test_sort(int *arr, int size) {
    int *copy = malloc(size * sizeof(int));
    memcpy(copy, arr, size * sizeof(int));
    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare);
    clock_t end = clock();
    printf("Time: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(copy);
}

int main() {
    int size = 10000000; 
    int *arr = malloc(size * sizeof(int));

    printf("Testing worst case (descending order)...\n");
    generate_descending(arr, size);
    test_sort(arr, size);

    printf("Testing best case (random)...\n");
    srand(time(NULL));
    for (int i = 0; i < size; i++) arr[i] = rand();
    test_sort(arr, size);

    free(arr);
    return 0;
}
