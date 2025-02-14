#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

typedef struct Block {
    int index;
    time_t timestamp;
    char data[256];
    char previousHash[65];
    char hash[65];
    struct Block* next;
} Block;

// Function to calculate SHA-256 hash
void calculateSHA256(const char* input, char* output) {
    SHA256_CTX sha256Context;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_Init(&sha256Context);
    SHA256_Update(&sha256Context, input, strlen(input));
    SHA256_Final(hash, &sha256Context);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}

// Function to calculate block hash
void calculateBlockHash(Block* block, char* output) {
    char input[512];
    snprintf(input, sizeof(input), "%d%ld%s%s", 
             block->index,
             block->timestamp,
             block->data,
             block->previousHash);
    calculateSHA256(input, output);
}

// Function to create a new block
Block* createBlock(int index, const char* data, const char* previousHash) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    
    newBlock->index = index;
    newBlock->timestamp = time(NULL);
    strncpy(newBlock->data, data, sizeof(newBlock->data) - 1);
    strncpy(newBlock->previousHash, previousHash, sizeof(newBlock->previousHash) - 1);
    newBlock->next = NULL;
    
    // Calculate this block's hash
    calculateBlockHash(newBlock, newBlock->hash);
    
    return newBlock;
}

// Function to validate the blockchain
int validateChain(Block* head) {
    Block* current = head;
    char calculatedHash[65];
    
    while (current->next != NULL) {
        calculateBlockHash(current, calculatedHash);
        
        // Verify current block's hash
        if (strcmp(calculatedHash, current->hash) != 0) {
            printf("Invalid block found at index %d\n", current->index);
            return 0;
        }
        
        // Verify the hash link
        if (strcmp(current->hash, current->next->previousHash) != 0) {
            printf("Invalid hash link found at index %d\n", current->index);
            return 0;
        }
        
        current = current->next;
    }
    
    return 1;
}

int main() {
    // Create genesis block
    Block* blockchain = createBlock(0, "Genesis Block", "0");
    
    // Add more blocks
    Block* block1 = createBlock(1, "Block 1 Data", blockchain->hash);
    blockchain->next = block1;
    
    Block* block2 = createBlock(2, "Block 2 Data", block1->hash);
    block1->next = block2;
    
    // Validate the chain
    printf("Blockchain validation result: %s\n", 
           validateChain(blockchain) ? "Valid" : "Invalid");
    
    // Display the blockchain
    Block* current = blockchain;
    while (current != NULL) {
        printf("\nBlock #%d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Data: %s\n", current->data);
        printf("Previous Hash: %s\n", current->previousHash);
        printf("Hash: %s\n", current->hash);
        current = current->next;
    }
    
    return 0;
}