// Keep this helper function
void reverseString(char* str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Keep the solution function
char* addBinary(char* a, char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB ? lenA : lenB) + 2;
    char* result = (char*)malloc(maxLen * sizeof(char));
    
    int i = lenA - 1;
    int j = lenB - 1;
    int k = 0;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }

        carry = sum / 2;
        result[k++] = (sum % 2) + '0';
    }

    result[k] = '\0';
    reverseString(result);
    
    return result; // The online judge will handle freeing this memory
}
