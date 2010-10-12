#include "ibitstream.h"

namespace huffman
{
	iBitStream::iBitStream(std::istream &i) : 
	in(i), byte(0), current_bit(0)
	{
	}

	iBitStream::bit_type iBitStream::get(void)
	{
		bit_type tmp = 0;      // This is an active bit placeholder.
		assert(current_bit < 8);
		if(current_bit == 0) byte = in.get();
		if(current_bit == 7){  // This test to see if the index is 7, then return the last bit
			tmp = (byte >> current_bit) & 0x1; // Active bit placeholder.
			flush();           // and flush both byte and current_bit.
			return tmp;        // Then return the saved value from the shift above.
		}
		if(current_bit < 8){
			tmp = (byte >> current_bit) & 0x1; 
			++current_bit;                     // Increase the index.
			return tmp;            // If not, it is safe to return the active bit.
		}
		return 0;  // This return should never execute, since current_bit will always be:
		           // (0) <= (current_bit) <= (7)
	}

	void iBitStream::flush(void)
	{
		current_bit = byte = 0;
	}
}