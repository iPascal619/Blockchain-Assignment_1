#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

// Structure for transactions within a block
typedef struct Transaction {
    char data[256];
    struct Transaction* next;
} Transaction;

// Enhanced block structure with transactions
typedef struct Block {
    int index;
    time_t timestamp;
    Transaction* transactions;
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

// Function to calculate block hash including all transactions
void calculateBlockHash(Block* block, char* output) {
    char input[4096] = {0};
    char temp[512];
    
    // Include block header information
    snprintf(temp, sizeof(temp), "%d%ld%s", 
             block->index,
             block->timestamp,
             block->previousHash);
    strcat(input, temp);
    
    // Include all transactions
    Transaction* currentTx = block->transactions;
    while (currentTx != NULL) {
        strcat(input, currentTx->data);
        currentTx = currentTx->next;
    }
    
    calculateSHA256(input, output);
}

// Function to create a new block
Block* createBlock(int index, const char* previousHash) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    
    newBlock->index = index;
    newBlock->timestamp = time(NULL);
    newBlock->transactions = NULL;
    strncpy(newBlock->previousHash, previousHash, sizeof(newBlock->previousHash) - 1);
    newBlock->next = NULL;
    
    // Initial hash calculation (Thiswill be updated as transactions are added)
    calculateBlockHash(newBlock, newBlock->hash);
    
    return newBlock;
}

// Function to add a transaction to a block
void addTransaction(Block* block, const char* data) {
    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    strncpy(newTransaction->data, data, sizeof(newTransaction->data) - 1);
    newTransaction->next = NULL;
    
    if (block->transactions == NULL) {
        block->transactions = newTransaction;
    } else {
        Transaction* current = block->transactions;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTransaction;
    }
    
    // Update block hash after adding transaction
    calculateBlockHash(block, block->hash);
}

// Function to save blockchain to file
void saveBlockchain(Block* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing\n");
        return;
    }
    
    Block* currentBlock = head;
    while (currentBlock != NULL) {
        // Write block header
        fwrite(currentBlock, sizeof(Block), 1, file);
        
        // Write transactions
        Transaction* currentTx = currentBlock->transactions;
        while (currentTx != NULL) {
            fwrite(currentTx, sizeof(Transaction), 1, file);
            currentTx = currentTx->next;
        }
        
        currentBlock = currentBlock->next;
    }
    
    fclose(file);
}

// Function to load blockchain from file
Block* loadBlockchain(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file for reading\n");
        return NULL;
    }
    
    Block* head = NULL;
    Block* current = NULL;
    Block tempBlock;
    
    while (fread(&tempBlock, sizeof(Block), 1, file) == 1) {
        Block* newBlock = (Block*)malloc(sizeof(Block));
        memcpy(newBlock, &tempBlock, sizeof(Block));
        newBlock->next = NULL;
        newBlock->transactions = NULL;
        
        // Read transactions
        Transaction tempTx;
        while (fread(&tempTx, sizeof(Transaction), 1, file) == 1) {
            Transaction* newTx = (Transaction*)malloc(sizeof(Transaction));
            memcpy(newTx, &tempTx, sizeof(Transaction));
            newTx->next = NULL;
            
            if (newBlock->transactions == NULL) {
                newBlock->transactions = newTx;
            } else {
                Transaction* currentTx = newBlock->transactions;
                while (currentTx->next != NULL) {
                    currentTx = currentTx->next;
                }
                currentTx->next = newTx;
            }
        }
        
        if (head == NULL) {
            head = newBlock;
            current = head;
        } else {
            current->next = newBlock;
            current = newBlock;
        }
    }
    
    fclose(file);
    return head;
}

// Main function 
int main() {
    // Create genesis block
    Block* blockchain = createBlock(0, "0");
    addTransaction(blockchain, "Genesis Transaction");
    
    // Add blocks with transactions
    Block* block1 = createBlock(1, blockchain->hash);
    addTransaction(block1, "Alice sends 50 BTC to Bob");
    addTransaction(block1, "Charlie sends 30 BTC to David");
    blockchain->next = block1;
    
    // Save blockchain to file
    saveBlockchain(blockchain, "blockchain.dat");
    
    // Load blockchain from file
    Block* loadedChain = loadBlockchain("blockchain.dat");
    
    // Display the loaded blockchain
    Block* current = loadedChain;
    while (current != NULL) {
        printf("\nBlock #%d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Previous Hash: %s\n", current->previousHash);
        printf("Hash: %s\n", current->hash);
        
        printf("Transactions:\n");
        Transaction* currentTx = current->transactions;
        while (currentTx != NULL) {
            printf("- %s\n", currentTx->data);
            currentTx = currentTx->next;
        }
        
        current = current->next;
    }
    
    return 0;
}