#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

// Node structure for Huffman Tree
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// Function to build Huffman Tree
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Create a leaf node for each character and add it to the min-heap
    for (auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build the Huffman Tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Function to generate Huffman codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->data] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to compress the file
void compressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::in);
    if (!inFile) {
        cerr << "Error: Could not open input file!" << endl;
        return;
    }

    // Step 1: Calculate character frequencies
    unordered_map<char, int> freqMap;
    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
    }
    inFile.close();

    // Step 2: Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // Step 3: Generate Huffman codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Step 4: Write compressed data to output file
    ofstream outFile(outputFile, ios::out | ios::binary);
    if (!outFile) {
        cerr << "Error: Could not open output file!" << endl;
        return;
    }

    // Write Huffman codes to the output file (for decompression)
    outFile << huffmanCode.size() << endl;
    for (auto& pair : huffmanCode) {
        outFile << pair.first << " " << pair.second << endl;
    }

    // Write compressed data
    inFile.open(inputFile, ios::in);
    string compressedData = "";
    while (inFile.get(ch)) {
        compressedData += huffmanCode[ch];
    }
    inFile.close();

    // Write the compressed data as binary
    for (size_t i = 0; i < compressedData.size(); i += 8) {
        string byte = compressedData.substr(i, 8);
        bitset<8> bits(byte);
        outFile.put(static_cast<char>(bits.to_ulong()));
    }

    outFile.close();
    cout << "File compressed successfully!" << endl;
}

// Function to decompress the file
void decompressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::in | ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open input file!" << endl;
        return;
    }

    // Read Huffman codes from the input file
    int codeSize;
    inFile >> codeSize;
    inFile.get(); // Skip newline

    unordered_map<string, char> huffmanCode;
    for (int i = 0; i < codeSize; i++) {
        char ch;
        string code;
        inFile.get(ch);
        inFile >> code;
        inFile.get(); // Skip newline
        huffmanCode[code] = ch;
    }

    // Read compressed data
    string compressedData = "";
    char byte;
    while (inFile.get(byte)) {
        bitset<8> bits(byte);
        compressedData += bits.to_string();
    }
    inFile.close();

    // Decode the compressed data
    ofstream outFile(outputFile, ios::out);
    if (!outFile) {
        cerr << "Error: Could not open output file!" << endl;
        return;
    }

    string currentCode = "";
    for (char bit : compressedData) {
        currentCode += bit;
        if (huffmanCode.find(currentCode) != huffmanCode.end()) {
            outFile.put(huffmanCode[currentCode]);
            currentCode = "";
        }
    }

    outFile.close();
    cout << "File decompressed successfully!" << endl;
}

// Main function
int main() {
    string inputFile, outputFile;
    int choice;

    cout << "1. Compress File\n2. Decompress File\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter input file name: ";
        cin >> inputFile;
        cout << "Enter output file name: ";
        cin >> outputFile;
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        cout << "Enter input file name: ";
        cin >> inputFile;
        cout << "Enter output file name: ";
        cin >> outputFile;
        decompressFile(inputFile, outputFile);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}