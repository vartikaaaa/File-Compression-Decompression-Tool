# Huffman Coding File Compression and Decompression Tool

A C++ implementation of the **Huffman Coding algorithm** for file compression and decompression. This project demonstrates the use of data structures (trees, priority queues, hash maps) and algorithms (greedy algorithms, tree traversals) to efficiently compress and decompress text files.

## **Features**
- **Compression**:
  - Compresses text files using Huffman Coding.
  - Generates a binary file containing the compressed data and Huffman codes.
- **Decompression**:
  - Decompresses the binary file back to the original text file.
- **Command-Line Interface**:
  - Easy-to-use command-line interface for compression and decompression.
- **Efficient**:
  - Uses a priority queue (min-heap) to build the Huffman tree efficiently.
  - Handles large files by processing data in chunks.

---

## **How It Works**
1. **Compression**:
   - Reads the input file and calculates the frequency of each character.
   - Builds a Huffman tree using a priority queue (min-heap).
   - Generates Huffman codes for each character.
   - Writes the Huffman codes and compressed binary data to the output file.

2. **Decompression**:
   - Reads the Huffman codes and compressed binary data from the input file.
   - Reconstructs the original text using the Huffman codes and writes it to the output file.

### Steps
1. Clone the repository:
2. Compile the code.
3. Choose 1 to compress the file or 2 to decompress the file.
4. Enter the input and output files

#### **Applications**
- **File Compression**: Reduces the size of text files for storage or transmission.
- **Educational Tool**: Helps students and developers understand Huffman Coding and its implementation.
- **Real-World Use**: Similar algorithms are used in file formats like ZIP and image formats like JPEG.

#### **Future Enhancements**
- Support for compressing binary files (e.g., images, videos).
- Integration with a graphical user interface (GUI).
- Performance optimization for large files.
