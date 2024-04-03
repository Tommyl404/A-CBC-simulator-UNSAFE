#include <iostream>
#include <vector>
#include <string>

//CODE FOR CBC MODE (UNSECURE UNDER CPA ATTACK BECAUSE OF THE USE OF NOT-PRF FUNCTION

// Helper function to convert a character to its binary representation as a string
std::string charToBinary(char c) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        result += ((c >> i) & 1) ? '1' : '0';
    }
    return result;
}

// Converts a string of text to its binary representation
std::string stringToBinary(const std::string& text) {
    std::string binaryString;
    for (char c : text) {
        binaryString += charToBinary(c);
    }
    return binaryString;
}

// Simple XOR function for two binary strings
std::string xorBinaryStrings(const std::string& a, const std::string& b) {
    std::string result;
    for (size_t i = 0; i < a.size(); ++i) {
        result += (a[i] == b[i % b.size()]) ? '0' : '1';
    }
    return result;
}

// CBC mode encryption using simple XOR-based encryption, operating on binary strings
std::vector<std::string> encryptCBC(const std::vector<std::string>& plaintextBlocks, const std::string& iv, const std::string& key) {
    std::vector<std::string> ciphertextBlocks;
    std::string previousBlock = iv;

    for (const auto& block : plaintextBlocks) {
        // XOR current plaintext block with the previous ciphertext block
        std::string xoredBlock = xorBinaryStrings(block, previousBlock);

        // "Encrypt" the XORed block (here, just another XOR with the key for demonstration)
        std::string encryptedBlock = xorBinaryStrings(xoredBlock, key);

        // Append to the ciphertext blocks
        ciphertextBlocks.push_back(encryptedBlock);

        // Set this block as the previous block for the next iteration
        previousBlock = encryptedBlock;
    }

    return ciphertextBlocks;
}

int main() {
    // Example usage with binary strings (each character represents a bit)
    std::vector<std::string> plaintextBlocks = {
        stringToBinary("hello"), // Convert string to binary representation for demonstration
        stringToBinary("world")
    };

    for (size_t i = 0; i < plaintextBlocks.size(); ++i) {
        std::cout << "plaintextBlock #" << (i + 1) << ": " << plaintextBlocks[i] << std::endl;
    }

    std::string iv = stringToBinary("initIV"); // Example IV, converted to binary
    std::string key = stringToBinary("key123"); // Example key, converted to binary

    auto ciphertextBlocks = encryptCBC(plaintextBlocks, iv, key);

    for (size_t i = 0; i < ciphertextBlocks.size(); ++i) {
        std::cout << "ciphertextBlock #" << (i + 1) << ": " << ciphertextBlocks[i] << std::endl;
    }

    return 0;
}
