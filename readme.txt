
This program uses the huffman algorithm in order to compress files.  
The huffman algorithm itself works best on textual data, and so it holds
that in order to have appropriate compression ratios, textual data 
must be provided.

A quick caveat: very small files would actually grow in size when compressed.
This is because I store a header on the compressed file.

The included binary works under Linux.  Specifically, under Ubuntu.
