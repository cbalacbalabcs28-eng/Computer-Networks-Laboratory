#include <stdio.h>
#include <string.h>

void solve() {
    char s[1005];
    scanf("%s", s);
    int sum = 0;
    int len = strlen(s);
  for (int i = 0; i < len; i++) {
        // Check if the current character is a numeric digit between '0' and '9'
        if (s[i] >= '0' && s[i] <= '9') {
            // Convert character digit to its actual integer value by subtracting '0'
            sum += (s[i] - '0');
        }
    }
    
    // Output the total sum for the current test case followed by a newline
    printf("%d\n", sum);
}

int main() {
    int t;
    // Read the total number of test cases
    if (scanf("%d", &t) == 1) {
        // Loop through all T test cases
        while (t--) {
            solve();
        }
    }
    return 0;
}
