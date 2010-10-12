// Interface for the oBitStream class

#ifndef OBITSTREAM_H
#define OBITSTREAM_H

#include <ostream>
#include <cassert>

namespace huffman 
{
	class oBitStream 
	{
	public:
		typedef unsigned char uchar;
		typedef unsigned int  size_type;
		typedef unsigned int  bit_type;

		oBitStream(std::ostream &o);
		//Precondition: Needs a reference to ostream as a formal parameter.  All parameter 
		//              instances would require a formal parameter that either derives from ostream
		//              or are ostream themselfs.
		//Postcondition: All members are initialized to zero, and the ostream instance class 
		//               is assigned to the member out, which is itself an ostream instance.

		void put(oBitStream::bit_type bit);
		//Precondition: Valid input are of bit_type, either 1 or 0.
		//Postcondition: Puts a single bit at position: current_bit.  It then puts a 
		//               entirely filled byte onto the output byte buffer.  On its completion,
		//               current_bit is set to 7, so that the function can reset.

		void flush(void);
		//Postcondition: Clears the current_bit and byte.

		void close(void);
		//Precondition: The last byte is being written to.
		//Postcondition: Simply enables the writting of the byte to the output buffer.

	private:
		std::ostream &out;           
		uchar        byte;
		size_type    current_bit;
	};
}

#endif