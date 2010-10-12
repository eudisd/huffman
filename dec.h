// Interface file for the decompression (Dec) class

#ifndef DEC_H
#define DEC_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include "ibitstream.h"
#include "node.h"

namespace huffman
{
	class Dec
	{
	public:
		enum { MAX = 256 };
		typedef unsigned int size_type;
		typedef std::stack<iBitStream::bit_type> BitString;

		Dec(void);
		// Postconditions: 
		// Preconditions:
		Dec(const char *in, const char *out);
		// Postconditions: 
		// Preconditions:
		~Dec(void);
		// Postconditions: 
		// Preconditions:
		unsigned char decode(NodePtr head, iBitStream &strm);
		// Postcondition:
		// Precondition:
		void decompress(void);
		// Postconditions: 
		// Preconditions:
		void read(std::ifstream &in);
		// Postconditions: 
		// Preconditions:
		void build(void);
		// Postconditions: 
		// Preconditions:
		void write(void);
		// Postconditions: 
		// Preconditions:

		// Mutators/Accessors
		void set_head(NodePtr h);
		// Postconditions: 
		// Preconditions:
		void set_iname(std::string s);
		// Postconditions: 
		// Preconditions:
		void set_oname(std::string s);
		// Postconditions: 
		// Preconditions:
		void set_cofsize(size_type f);
		// Postconditions: 
		// Preconditions:
		NodePtr get_head(void)const;
		// Postconditions: 
		// Preconditions:
		std::string &get_iname(void);
		// Postconditions: 
		// Preconditions:
		std::string &get_oname(void);
		// Postconditions: 
		// Preconditions:
		size_type get_cofsize(void)const;
		// Postconditions: 
		// Preconditions:

	private:
		std::string iname;
		std::string oname;
		NodePtr head;
		std::vector<NodePtr> buffer;
		std::priority_queue< NodePtr, 
			                 std::vector<NodePtr>, 
			                 std::greater<NodePtr> > queue;

		size_type co_fsize;
	};
}

#endif