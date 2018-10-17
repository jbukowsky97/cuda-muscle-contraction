#include <stdio.h>
#include <stdlib.h>

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

    unsigned long long int totalWork = 0;

    int temp;
    int force;
    int distance;
    for (unsigned long long int i = 0; i < n; i++) {
        temp = i % n;
        if (temp < leftMiddle) {
            force = middle - (leftMiddle - temp);
        } else if (temp == leftMiddle || temp == middle) {
            force = middle;
        } else {
            force = n - temp;
        }
        distance = i % 10 + 1;

        totalWork += force * distance;
    }

    printf("Total Work:\t%lld\n", totalWork);
}