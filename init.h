#ifndef INIT_H
#define INIT_H

// Interface file for the initial processes

/**
* This is just a wrapper class for the initial processes.
* I wrote it, primarily, to encapsulate the main() startup.
* It also includes all of the necessary headers for the main()
* function to work properly.
**/

#include <iostream>  
#include <cstdlib>
#include <string.h> // Added Mon, Aug 2 2010

#include "co.h"
#include "dec.h"

namespace huffman
{
	using namespace std;
	class Init {
	public:
		Init(int c, char *v[]);
		void start(void);
		void print_init(void);
		void print_help(void);
		void print_version(void);
		// Accessors
		int get_ac(void);    // argument c
		char **get_av(void); // argument v
	private:
		int ac;
		char **av;
		int MAJ_VER; 
		int MIN_VER;
		int BUG_VER;
	};
}

#endif
