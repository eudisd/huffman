// Implementation file for the decompression (Dec) class

#include "dec.h"

namespace huffman
{
	Dec::Dec(const char *in, const char *out) :
	head(NULL),
	co_fsize(0), iname(in), oname(out)
	{
		for(int i = 0; i < MAX ; i++){
			NodePtr tmp = new Node;
			tmp->set_data(i);
			tmp->set_weight(0);
			tmp->set_parent(NULL);
			tmp->set_left(NULL);
			tmp->set_right(NULL);
			buffer.push_back(tmp);
		}
	}
	Dec::~Dec(void)
	{
		for(int i = 0; i < MAX ; i++)
			delete buffer[i];
	}
	unsigned char Dec::decode(NodePtr head, iBitStream &strm)
	{
		unsigned int path;
		while(head != NULL){
			if(head->get_left() == NULL || head->get_left() == NULL)
				return head->get_data();
			path = strm.get();
			if(path == 0){
				head = head->get_left();
			}
			else if (path == 1){
				head = head->get_right();
			}
		}
		return NULL;
	}

	void Dec::decompress(void)
	{
		write();
	}

	void Dec::read(std::ifstream &in)
	{
		iBitStream instrm(in);
		int i;
		unsigned int tmp = 0, tmp_freq = 0;
		// Read in the first 32-bit integer
		for(i = 0; i < (sizeof(unsigned int)*8); i++){
			tmp = instrm.get();
			tmp <<= i; 
			co_fsize |= tmp;
		}

		// Read in the next 256 32-bit integers into buffer[] vector
		for(i = 0; i < MAX; i++){
			for(int j = 0; j < (sizeof(unsigned int)*8); j++){
				tmp = instrm.get();
				tmp <<= j; 
				tmp_freq |= tmp;
			}
			buffer[i]->set_weight(tmp_freq);
			tmp = tmp_freq = 0;
		}
	}
	void Dec::build(void)
	{
		// These two processes are identical to the ones in the Co class.
		for(int i = 0; i < MAX; i++){
			if(buffer[i]->get_weight() > 0){      
				NodePtr tmp = new Node;          
				tmp->set_data(buffer[i]->get_data());
				tmp->set_weight(buffer[i]->get_weight());
				queue.push(tmp);
			}
		}
		while( queue.size() > 1 ){
			NodePtr right = queue.top();        // Put the first lowest priority Node in right.
			queue.pop();                        // Erase that Node from queue.
			NodePtr left  = queue.top();        // Put the second lowest priority Node in left.
			queue.pop();                        // Erase that second Node from queue.
			// Finally, merge the two nodes (left and right), and then push it back on the queue
			queue.push(left->merge(right));
		}
		head = queue.top();
	}
	void Dec::write(void)
	{
		std::ifstream in(iname.c_str(), std::ios::binary); // Binary mode input
		std::ofstream out(oname.c_str()); // Text mode output
		NodePtr address_at_found = NULL;  // 
		if(in.is_open() && out.is_open()){
			read(in);  // Read the header section and prefix codes;
			build();   // Build the tree from the just-read information
	
			iBitStream i(in);

			std::cout << "Decompressing data...\n";
			while(!in.eof()){
				out.put(decode(head, i));
			}
		}
		in.close();
		in.clear();
		out.close();
		out.clear();
	}

	void Dec::set_head(NodePtr h) { head = h; }
	void Dec::set_iname(std::string s) { iname = s; }
	void Dec::set_oname(std::string s) { oname = s; }
	void Dec::set_cofsize(size_type f) { co_fsize = f; }

	NodePtr Dec::get_head(void)const  { return head; }
	std::string &Dec::get_iname(void) { return iname; }
	std::string &Dec::get_oname(void) { return oname; }
	Dec::size_type Dec::get_cofsize(void)const { return co_fsize; }

}