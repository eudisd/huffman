// Interface file for the class Node.

#ifndef NODE_H
#define NODE_H

namespace huffman
{
	class Node;
	typedef Node*  NodePtr;
	typedef Node** NodePtrPtr;

	class Node
	{
	public:
		typedef unsigned char data_type;
		typedef unsigned int  weight_type;
		Node(void);
		Node(NodePtr p, NodePtr l, NodePtr r, data_type data, weight_type weight);

		void find(NodePtr head, NodePtrPtr ref, data_type target);
		// Postcondition:
		// Precondition:

		bool leaf(void);
		// Postcondition: Returns true if one of the links is NULL, false otherwise.

		NodePtr merge(const NodePtr other);
		// Precondition: The formal parameter should point to a valid Node instance.
		// Postcondition: The merge function uses the current instance and the passed instance of
		//                type Node.  It then returns a pointer to a new allocated Node pointer that 
		//                contains both its links pointed to the previous Nodes used; essentially
		//                merging the two.  Further, the weights of both of the used Nodes are added
		//                and assigned to the new allocated parent Node's weight field.

		// Mutators
		void set_data(data_type d);
		void set_weight(weight_type w);
		void set_parent(NodePtr p);
		void set_left(NodePtr l);
		void set_right(NodePtr r);
		void assign(NodePtr p, NodePtr l, NodePtr r, data_type data, weight_type weight);

		// Accessors
		data_type get_data(void)const;
		weight_type get_weight(void)const;
		NodePtr get_parent(void)const;
		NodePtr get_left(void)const;
		NodePtr get_right(void)const;


	private:
		data_type   data;
		weight_type weight;
		NodePtr     parent;
		NodePtr     left;
		NodePtr     right;
	};
}
#endif