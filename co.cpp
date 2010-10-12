// Implementation file for Co class (Compression)

#include "co.h"

namespace huffman
{
	Co::Co(const char *i, const char *o) :
	head(NULL), iname(i), oname(o),
	fsize(0)
	{
		for(int j = 0; j < MAX ; j++){
			NodePtr tmp = new Node;    // Here I allocate 256 nodes from heap
			table[j] = 0;              // Initialize all frequencies in the header table
			tmp->set_data(j);     
			tmp->set_weight(0);
			tmp->set_parent(NULL);
			tmp->set_left(NULL);
			tmp->set_right(NULL);
			buffer.push_back(tmp); 
		}
		computefsize();                // Compute file size.
	}
	Co::~Co(void)
	{ // Deallocate the buffer with 256 nodes in it.
		for(size_t i = 0; i < buffer.size() ; i++)
			delete buffer[i];
	}
	void Co::compress(void)
	{
		build();
		write();
	}

	Co::BitString *Co::encode(NodePtr at_found)
	{
		Co::BitString *bitstr = new Co::BitString;
		while(at_found->get_parent() != NULL){
			if(at_found == at_found->get_parent()->get_left())
				bitstr->push(0);
			
			else if (at_found == at_found->get_parent()->get_right())
				bitstr->push(1);
				
			at_found = at_found->get_parent(); // Go up one level in tree depth
		}
		return bitstr;
	}
	void Co::find(NodePtr head, NodePtrPtr ref, Node::data_type target)
	{
		if(head == NULL) return;
		else if(head->get_data() == target){
			*ref = head;
			return;
		}
		else {
			find(head->get_left(), ref, target);
			find(head->get_right(), ref, target);
		}
	}

	void Co::build(void)
	{
		// COUNT THE FREQUENCIES 
		int i;
		std::ifstream in(iname.c_str(), std::ios::binary); 
										   
		if(in.is_open()){
			while(!in.eof()){
				Node::data_type c = in.get();
				for(i = 0; i < MAX; i++)
					if(i == c) {
						table[i]++;            // Increment table frequencies
						buffer[i]->set_weight(table[i]);
					}
			}
		}
		in.close(); 
		in.clear(); 

		// LOAD THE QUEUE FROM BUFFER
		for(i = 0; i < MAX; i++){
			if(buffer[i]->get_weight() != 0){      
				NodePtr tmp = new Node;          
				tmp->set_data(buffer[i]->get_data());
				tmp->set_weight(buffer[i]->get_weight());
				queue.push(tmp);
			}
		}

		// BUILD THE HUFFMAN TREE
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

	// WRITE PREFIX CODES
	/**
	* This would constitute the second pass to file.
	**/
	void Co::write(void)
	{
		std::cout << "\n\nCompresssing data....\n\n";
		std::ifstream in(iname.c_str(), std::ios::binary);
		std::ofstream out(oname.c_str(), std::ios::binary);

		BitString *prefix;
		NodePtr address_at_found = NULL;

		if(out.is_open() && in.is_open()){
			header(out);               // Write out the header
			oBitStream outstream(out); // Open the oBitStream for prefix code writing
			while(!in.eof()){
				Node::data_type c = in.get();
				find(head, &address_at_found, c);
				prefix = encode(address_at_found);
				while(prefix->size() != 0){ 
					outstream.put(prefix->top());
					prefix->pop();
				}
			}
		}
		out.close();
		out.clear();
		in.close();
		in.clear();
	}
	void Co::header(std::ostream &o)
	{
		// First integer in header holds the uncompressed file size
		int i;
		for(i = 0 ; i < sizeof(unsigned int)*8; i=i+8){
			o.put(((fsize >> i)&0xff));
		}

		// Frequency table is written here
		for(i = 0; i < MAX; i++){
			for(int j = 0 ; j < sizeof(unsigned int)*8; j=j+8)
				o.put(((table[i] >> j)&0xff));
		}
	}

	void Co::computefsize(void)
	{
		std::ifstream in(iname.c_str());
		Co::size_type start = 0, end = 0;
		if(in.is_open()){
			start = in.tellg();
			in.seekg(0, std::ios::end);
			end   = in.tellg();
		}
		in.close();
		in.clear();
		fsize = end - start;
	}

	// Mutators/Accessors
	void Co::set_head(NodePtr h)      { head  = h; }
	void Co::set_iname(std::string s) { iname = s; }
	void Co::set_oname(std::string s) { oname = s; }
	void Co::set_fsize(size_type f)   { fsize = f; }

	NodePtr Co::get_head(void)const         { return head;  }
	std::string &Co::get_iname(void)        { return iname; }
	std::string &Co::get_oname(void)        { return oname; }
	Co::size_type *Co::get_table(void)const { return (Co::size_type*)(&table); }
	Co::size_type Co::get_fsize(void)const  { return fsize; }
}