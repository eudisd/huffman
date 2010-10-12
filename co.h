// Interface file for Co class (Compression)

#ifndef CO_H
#define CO_H

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>
#include <ostream>
#include <istream>
#include <fstream>
#include "node.h"
#include "obitstream.h"

namespace huffman
{
	class Co
	{
	public:
		typedef std::stack<oBitStream::bit_type> BitString;
		typedef unsigned int size_type;
		enum { MAX = 256 }; // HEADER_SIZE = 256 + 1 ints

		Co(const char *i, const char *o);
		// Precondition:
		// Postcondition:

		~Co(void);
		// Precondition:
		// Postcondition:

		BitString *encode(NodePtr at_found);
		// Precondition:
		// Postcondition:

		void find(NodePtr head, NodePtrPtr ref, Node::data_type target);
		// Postcondition:
		// Precondition:

		void compress(void);
		// Precondition:
		// Postcondition:

		void build(void);
		// Precondition:
		// Postcondition:

		void write(void);
		// Precondition:
		// Postcondition:

		void header(std::ostream &o);
		// Precondition:
		// Postcondition:

		void computefsize(void);
		// Precondition:
		// Postcondition:

		// Mutators/Accessors
		void set_head(NodePtr h);
		void set_iname(std::string s);
		void set_oname(std::string s);
		void set_fsize(size_type f);
		NodePtr get_head(void)const;
		std::string &get_iname(void);
		std::string &get_oname(void);
		size_type *get_table(void)const;
		size_type get_fsize(void)const;

	private:
		size_type table[MAX];           // Header. Should hold frequencies only. 
		std::vector<NodePtr> buffer;    // A buffer to utilize only non-empty frequency nodes.
		NodePtr head;                   // Huffman tree head pointer
		std::priority_queue< NodePtr,                        // Allocator type
						     std::vector<NodePtr>,           // Adapter class
			                 std::greater<NodePtr> > queue;  // Comparator
		std::string iname;    // Input file name
		std::string oname;    // Output file name
		size_type fsize;      // Holds total file size, in bytes
	};
}
#endif

 