README
======
Huffman Compiler (C++)
----------------------

This program uses the huffman algorithm to compress files.  
The huffman algorithm itself works best on textual data, and so it holds
that in order to have appropriate compression ratios, textual data 
must be provided.

A quick caveat: very small files would actually grow in size when compressed.
This is because a header is stored in the compressed file.

