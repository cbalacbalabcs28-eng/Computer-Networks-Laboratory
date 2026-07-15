#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for the Binary Trie
typedef struct TrieNode {
    struct TrieNode* children[2];
} TrieNode;

// Helper function to create a new Trie node
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->children[0] = NULL;
    node->children[1] = NULL;
    return node;
}

// Function to insert a number's bits into the Trie
void insert(TrieNode* root, int num) {
    TrieNode* curr = root;
    // Iterate from the most significant bit (30th bit for positive signed integers) down to 0
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (curr->children[bit] == NULL) {
            curr->children[bit] = createNode();
        }
        curr = curr->children[bit];
    }
}

// Function to find the maximum XOR possible for a given number using the Trie
int getMaxXOR(TrieNode* root, int num) {
    TrieNode* curr = root;
    int max_xor = 0;
    
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int toggled_bit = 1 - bit; // The ideal opposite bit we want to find
        
        // If the opposite bit exists, take it to maximize XOR
        if (curr->children[toggled_bit] != NULL) {
            max_xor |= (1 << i); // Set the i-th bit of the result to 1
            curr = curr->children[toggled_bit];
        } else {
            // Otherwise, we are forced to take the matching bit path (XOR results in 0)
            curr = curr->children[bit];
        }
    }
    return max_xor;
}

// Helper function to free allocated Trie memory to prevent memory leaks
void freeTrie(TrieNode* root) {
    if (root == NULL) return;
    freeTrie(root->children[0]);
    freeTrie(root->children[1]);
    free(root);
}

// MAIN FUNCTION called by the platform
int findMaximumXOR(int* nums, int numsSize) {
    if (numsSize < 2) return 0;
    
    TrieNode* root = createNode();
    int global_max_xor = 0;
    
    // Step 1: Insert the first number into the Trie
    insert(root, nums[0]);
    
    // Step 2: For every subsequent number, find its max XOR against existing items,
    // then insert it into the Trie
    for (int i = 1; i < numsSize; i++) {
        int current_max = getMaxXOR(root, nums[i]);
        if (current_max > global_max_xor) {
            global_max_xor = current_max;
        }
        insert(root, nums[i]);
    }
    
    // Clean up memory
    freeTrie(root);
    
    return global_max_xor;
}

