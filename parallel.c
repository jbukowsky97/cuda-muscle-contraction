#include <stdio.h>
#include <stdlib.h>

extern void gpuCalculate(int* work, int leftMiddle, int middle, int n);

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage:\n\t./sequential <vector size>\n");
        exit(EXIT_FAILURE);
    }

    const unsigned long long int n = strtoull(argv[1], NULL, 0);

    if (n % 2 != 0) {
        printf("vector size must be even\n");
        exit(EXIT_FAILURE);
    }

    const unsigned long long int middle = n / 2;
    const unsigned long long int leftMiddle = middle - 1;

    int* work = malloc(n * sizeof(int));

    gpuCalculate(work, leftMiddle, middle, n);

    unsigned long long int totalWork = 0;
    for (unsigned long long int i = 0; i < n; i++) {
        totalWork += work[i];
    }

    free(work);

    printf("Total Work:\t%lld\n", totalWork);
}