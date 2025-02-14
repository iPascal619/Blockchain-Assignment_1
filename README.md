# Blockchain Implementation in C

## Overview
This project implements a basic blockchain system in C, featuring SHA-256 hashing, block creation, transaction management, and chain validation. The implementation includes both basic and advanced features demonstrating core blockchain concepts.

## Project Structure
The project consists of three main components:
1. SHA-256 Implementation (Task 1)
2. Simple Blockchain (Task 2)
3. Complete Blockchain System (Implementation)

## Prerequisites
- C Compiler (GCC recommended)
- OpenSSL development libraries
- Basic understanding of blockchain concepts

## Installation

1. Install OpenSSL development libraries:
```bash
# For Ubuntu/Debian
sudo apt-get install libssl-dev

# For CentOS/RHEL
sudo yum install openssl-devel

# For macOS
brew install openssl
```

2. Clone the repository:
```bash
git clone <https://github.com/iPascal619/Blockchain-Assignment_1>
cd blockchain-Assignment_1
```

3. Compile the code:
```bash
# For SHA-256 implementation
gcc -o Task1 Task1.c -lssl -lcrypto

# For simple blockchain
gcc -o Task2 Task2.c -lssl -lcrypto

# For complete blockchain
gcc -o implementation implementation.c -lssl -lcrypto
```

## Components Description

### 1. SHA-256 Implementation(Task1)
- Location: `Task1.c`
- Features:
  - String input handling
  - SHA-256 hash calculation
  - Hexadecimal output formatting
- Usage:
  ```c
  char input[] = "Blockchain Cryptography";
  char output[65];
  calculateSHA256(input, output);
  ```

### 2. Simple Blockchain(Task2)
- Location: `Task2.c`
- Features:
  - Basic block structure
  - Chain linking
  - Hash validation
  - Simple data storage
- Usage:
  ```c
  Block* blockchain = createBlock(0, "Genesis Block", "0");
  Block* block1 = createBlock(1, "Block 1 Data", blockchain->hash);
  ```

### 3. Complete Blockchain System
- Location: `Implementation.c`
- Features:
  - Advanced block structure
  - Transaction management
  - Chain validation
  - File persistence
  - Memory management
- Usage:
  ```c
  Block* blockchain = createBlock(0, "0");
  addTransaction(blockchain, "Genesis Transaction");
  saveBlockchain(blockchain, "blockchain.dat");
  ```

## Task Details

### Question One
#### Task 1: SHA-256 Implementation
- Implements SHA-256 hashing algorithm
- Takes string input
- Produces hexadecimal hash output
- Includes detailed comments

#### Task 2: Simple Blockchain
- Basic blockchain structure
- Block linking
- Hash validation
- Chain integrity verification

### Question Two
#### Task 1: Block Structure
- Comprehensive block definition
- Transaction support
- Hash linking
- Timestamp management

#### Task 2: Blockchain Creation
- Chain management
- Block linking
- Hash verification
- Integrity validation

#### Task 3: Transaction Simulation
- Transaction structure
- Multiple transaction support
- Transaction validation
- Hash updates

#### Task 4: Blockchain Persistence
- File saving functionality
- Chain loading
- Data integrity verification
- Error handling

## Error Handling
The implementation includes error handling for:
- File operations
- Memory allocation
- Invalid inputs
- Chain validation

## Memory Management
- Proper allocation and deallocation
- Memory leak prevention
- Resource cleanup
- Transaction memory handling

## Security Considerations
- Hash validation
- Chain integrity
- Transaction verification
- Data persistence security

## Contributing
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License
This project is licensed under the MIT License 

## Acknowledgments
- OpenSSL for cryptographic functions
- Blockchain technology concepts
- C programming best practices

## Author
Chukwuma PAscal ONuoha

## Version History
- v1.0.0 - Initial release
