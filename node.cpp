// Implementation file for Node class

#include <iostream>
#include <cstdlib>
#include "node.h"

namespace huffman
{
	Node::Node(void):
	left(NULL), right(NULL), parent(NULL),
	data(0), weight(0)
	{
	}

	Node::Node(NodePtr p, NodePtr l, NodePtr r, data_type d, weight_type w) :
	left(l), right(r), parent(p),
	data(d), weight(w)
	{
	}

	void Node::find(NodePtr head, NodePtrPtr ref, data_type target)
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
	bool Node::leaf(void) 
	{ 
		if(left == NULL || right == NULL)return true;
		else return false;
	}

	void Node::assign(NodePtr p, NodePtr l, NodePtr r, data_type d, weight_type w)
	{
		data   = d;
		weight = w;
		parent = p;
		left   = l;
		right  = r;
	}

	NodePtr Node::merge(const NodePtr other)
	{
		NodePtr tmp   = new Node;               // Create new node
		tmp->weight   = other->weight + weight; // Join frequencies
		other->parent = parent = tmp;           // Assign the parent to links
		tmp->left     = this;                   // The (this) pointer is equal to the left link
		tmp->right    = other;                  // The other is equal to the right link
		return tmp;                             
	}
	
	// Mutators/Accessors
	void Node::set_data(data_type d)    { data   = d;    }
	void Node::set_weight(weight_type w){ weight = w;    }
	void Node::set_parent(NodePtr p)    { parent = p;    }
	void Node::set_left(NodePtr l)      { left   = l;    }
	void Node::set_right(NodePtr r)     { right  = r;    }

	Node::data_type Node::get_data(void)     const { return data;   }
	Node::weight_type Node::get_weight(void) const { return weight; }
	NodePtr Node::get_parent(void)     const { return parent; }
	NodePtr Node::get_left(void)       const { return left;   }
	NodePtr Node::get_right(void)      const { return right;  }
}