#include <stdio.h>

void calculate_the_maximum(int n, int k) {
    int max_and = 0;
    int max_or = 0;
    int max_xor = 0;

    // Iterate through all unique pairs (a, b) where 1 <= a < b <= n
    for (int a = 1; a < n; a++) {
        for (int b = a + 1; b <= n; b++) {
            int current_and = a & b;
            int current_or = a | b;
            int current_xor = a ^ b;

            // Check and update maximum for AND
            if (current_and < k && current_and > max_and) {
                max_and = current_and;
            }
            // Check and update maximum for OR
            if (current_or < k && current_or > max_or) {
                max_or = current_or;
            }
            // Check and update maximum for XOR
            if (current_xor < k && current_xor > max_xor) {
                max_xor = current_xor;
            }
        }
    }

    // Print the results on separate lines
    printf("%d\n", max_and);
    printf("%d\n", max_or);
    printf("%d\n", max_xor);
}

int main() {
    int n, k;
    // Read input values for n and k
    if (scanf("%d %d", &n, &k) == 2) {
        calculate_the_maximum(n, k);
    }
    return 0;
}

