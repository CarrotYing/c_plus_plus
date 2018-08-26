#include "CompressFile.hpp"
int main()
{
    FileCompress f;
    f.Compress("test.txt");
    FileCompress f2;
    f2.UnCompress("test.txt.Huffman");
}
