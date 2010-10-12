#include "obitstream.h"

namespace huffman
{
	oBitStream::oBitStream(std::ostream &o) :      // Simple constructor
	out(o), byte(0), current_bit(0) 
	{                                             
	}
	void oBitStream::put(oBitStream::bit_type bit)
	{
		assert(current_bit < 8);
		if(current_bit == 7){
			if(bit == 1){
				bit <<= current_bit;
				byte |= bit;
			}
			out.put(byte);
			flush();	
		}
		else if(current_bit < 8){
			if(bit == 1){
				bit <<= current_bit;
				byte |= bit;
			}
			current_bit++;         
		}
	}
	void oBitStream::flush(void)
	{
		current_bit = byte = 0;
	}
	
	void oBitStream::close(void)
	{
		out.put(byte);   
	}
}