// Interface for the iBitStream class.

#ifndef IBITSTREAM_H
#define IBITSTREAM_H

#include <istream>
#include <cassert>

namespace huffman 
{
	class iBitStream 
	{
	public:
		typedef unsigned char uchar;      // Unsigned char used for byte shifting.
		typedef unsigned int  size_type;  // Unsigned int used for counting of bit position.
		typedef unsigned int  bit_type;   // The native bit type, either 0 or 1.

		iBitStream(std::istream &i);
		//Precondition: Needs a reference to istream as formal parameter.  All instances
		//              would require a formal parameter that either derives form istream
		//              or is an istream.
		//Postcondition: All members are initialized to zero, and the istream instance class 
		//               is assigned to the member in, which is itself an istream instance.

		bit_type get(void);
		//Precondition: byte must contain valid input for valid data to be processed.
		//Postcondition: Gets the bit data at current_bit by using left-shifts.  It returns
		//               the bit specified by current_bit.

		void flush(void);
		//Postcondition: Clears the current_bit and byte. 
		
	private:
		std::istream &in;
		uchar        byte;
		size_type    current_bit; 
	};
}
#endif
