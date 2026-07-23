#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert a text string to a binary string
void string_to_binary(const char *text, char *binary) {
    binary[0] = '\0';
    for (int i = 0; text[i] != '\0'; i++) {
        char val = text[i];
        for (int j = 7; j >= 0; j--) {
            if ((val >> j) & 1) {
                strcat(binary, "1");
            } else {
                strcat(binary, "0");
            }
        }
    }
}

// Function to convert a binary string back to a text string
void binary_to_string(const char *binary, char *text) {
    int len = strlen(binary);
    int char_idx = 0;

    for (int i = 0; i < len - (len % 8); i += 8) {
        char val = 0;
        for (int j = 0; j < 8; j++) {
            val <<= 1;
            if (binary[i + j] == '1') {
                val |= 1;
            }
        }
        text[char_idx++] = val;
    }
    text[char_idx] = '\0';
}

// Function to perform bit stuffing (Insert '0' after five consecutive '1's)
void bit_stuff(const char *input, char *output) {
    int count = 0;
    int j = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        output[j++] = input[i];
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                output[j++] = '0';
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    output[j] = '\0';
}

// Function to perform bit de-stuffing
void bit_destuff(const char *input, char *output) {
    int count = 0;
    int j = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        output[j++] = input[i];
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                if (i + 1 < len && input[i + 1] == '0') {
                    i++;
                }
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    output[j] = '\0';
}

int main() {
    char input_string[100];
    char original_binary[800];
    char stuffed_frame[1000];
    char transmitted_frame[1000];
    char received_frame[1000];
    char destuffed_binary[1000];
    char recovered_string[100];
    int choice;
    int error_pos, num_errors;

    printf("=== BIT STUFFING===\n");
    printf("Enter input string (e.g., A~B): ");
    scanf("%99[^\n]", input_string);

    // 1. Convert text to binary
    string_to_binary(input_string, original_binary);

    // 2. Sender Side: Bit Stuffing
    bit_stuff(original_binary, stuffed_frame);
    strcpy(transmitted_frame, stuffed_frame);
    strcpy(received_frame, transmitted_frame); // Copy clean data first

    int frame_len = strlen(transmitted_frame);

    // 3. Error Choice Menu
    printf("\nStuffed Frame Length is %d bits (Indices: 0 to %d)\n", frame_len, frame_len - 1);
    printf("Select Error Injection Type:\n");
    printf("0: No Error\n");
    printf("1: Single-Bit Error\n");
    printf("2: Multiple-Bit Error (Burst)\n");
    printf("Enter choice (0/1/2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Single-bit injection position
        printf("Enter the bit position to flip (0 to %d): ", frame_len - 1);
        scanf("%d", &error_pos);

        if (error_pos >= 0 && error_pos < frame_len) {
            received_frame[error_pos] = (received_frame[error_pos] == '1') ? '0' : '1';
            printf("\n[!] Bit flipped successfully at index %d!\n", error_pos);
        } else {
            printf("\n[x] Invalid position! Transmitting data without errors.\n");
        }
    }
    else if (choice == 2) {
        // Multiple-bit injection details
        printf("How many bits do you want to flip? ");
        scanf("%d", &num_errors);

        printf("Enter the starting bit position (0 to %d): ", frame_len - 1);
        scanf("%d", &error_pos);

        // Verify bounds for the burst loop
        if (error_pos >= 0 && error_pos < frame_len && num_errors > 0) {
            printf("\n[!] Flipping bits: ");
            for (int i = 0; i < num_errors; i++) {
                int current_pos = error_pos + i;

                // Stop if burst exceeds string limits
                if (current_pos >= frame_len) {
                    printf("\n[x] Reached end of frame sequence.");
                    break;
                }

                received_frame[current_pos] = (received_frame[current_pos] == '1') ? '0' : '1';
                printf("%d ", current_pos);
            }
            printf("\n");
        } else {
            printf("\n[x] Invalid parameters! Transmitting data without errors.\n");
        }
    }
    else {
        printf("\n[+] No errors injected. Clean transmission channel.\n");
    }

    // 4. Receiver Side: De-stuffing
    bit_destuff(received_frame, destuffed_binary);

    // 5. Integrity Verification via Frame Comparison
    int error_detected = 0;
    if (strcmp(transmitted_frame, received_frame) != 0) {
        error_detected = 1;
    }

    // 6. Convert recovered binary back to characters
    binary_to_string(destuffed_binary, recovered_string);

    // 7. Output Final Simulation Results Report
    printf("\n================== SIMULATION REPORT ==================\n");
    printf("Original Word     : %s\n", input_string);
    printf("Original Binary   : %s\n", original_binary);
    printf("Stuffed Frame     : %s\n", stuffed_frame);
    printf("Transmitted Frame : %s\n", transmitted_frame);
    printf("Received Frame    : %s\n", received_frame);
    printf("De-stuffed Data   : %s\n", destuffed_binary);

    if (error_detected == 0) {
        printf("Recovered Word    : %s\n", recovered_string);
        printf("Error Status      :  Transmission Successful. No Error Detected.\n");
    } else {
        printf("Recovered Word    : %s (CORRUPTED)\n", recovered_string);
        printf("Error Status      :  Transmission Failed. Error Detected via Frame Comparison!\n");
    }
    printf("=======================================================\n");

    return 0;
}
