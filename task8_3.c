#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 1000000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool is_sorted(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void test_case(const char *description, int *arr, int size) {
    int *copy = malloc(size * sizeof(int));
    memcpy(copy, arr, size * sizeof(int));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    qsort(copy, size, sizeof(int), compare);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if (is_sorted(copy, size)) {
        printf("%s - Time: %.6f sec - Sorted: OK\n", description, elapsed);
    } else {
        printf("%s - Sorted: ERROR!\n", description);
    }

    free(copy);
}

void generate_descending(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void generate_random(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void generate_equal_elements(int *arr, int size) {
    int value = rand();
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

void generate_alternating_pattern(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (i % 2 == 0) ? i : size - i;
    }
}

int main() {
    srand(time(NULL));
    int *arr = malloc(SIZE * sizeof(int));

    // Тест 1: Відсортований у зворотному порядку (класика)
    generate_descending(arr, SIZE);
    test_case("Descending Order", arr, SIZE);

    // Тест 2: Випадкові елементи
    generate_random(arr, SIZE);
    test_case("Random Order", arr, SIZE);

    // Тест 3: Однакові елементи
    generate_equal_elements(arr, SIZE);
    test_case("All Elements Equal", arr, SIZE);

    // Тест 4: Чередування великих і малих
    generate_alternating_pattern(arr, SIZE);
    test_case("Alternating Pattern", arr, SIZE);

    free(arr);
    return 0;
}
