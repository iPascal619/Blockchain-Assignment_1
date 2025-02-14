#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Function to convert bytes to hexadecimal string
void bytesToHexString(unsigned char* bytes, char* hexString, int length) {
    for(int i = 0; i < length; i++) {
        sprintf(hexString + (i * 2), "%02x", bytes[i]);
    }
    hexString[length * 2] = '\0';
}

// Function to calculate SHA-256 hash of a string
void calculateSHA256(const char* input, char* output) {
    SHA256_CTX sha256Context;
    
    // Buffer to store the raw hash bytes
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Initialize the SHA-256 context
    SHA256_Init(&sha256Context);
    
    // Process the input string
    SHA256_Update(&sha256Context, input, strlen(input));
    
    // Generate the final hash
    SHA256_Final(hash, &sha256Context);
    
    // Convert the hash bytes to hexadecimal string
    bytesToHexString(hash, output, SHA256_DIGEST_LENGTH);
}

int main() {
    char input[] = "Blockchain Cryptography";
    char output[65];  
    
    // Calculate the hash
    calculateSHA256(input, output);
    
    // Display the results
    printf("Input: %s\n", input);
    printf("SHA-256 Hash: %s\n", output);
    
    return 0;
}