#include "init.h"

namespace huffman
{
	Init::Init(int c, char *v[]) : ac(c), av(v),
		MAJ_VER(0), MIN_VER(9), BUG_VER(0)
	{	
	}
	void Init::start(void)
	{
		if(ac < 2) { print_init(); }            // Print the initial information if only
		else {                                  // the program name is inputted.
			try {
				if(!strcmp(av[1], "--help")){   // Print the help screen if the proper input
					print_help();               // option is passed.
				}
				else if(!strcmp(av[1], "--version")){ 
					print_version();            // Print the version information if the proper
				}                               // option is provided.
				else if((!strcmp(av[1], "-c") || !strcmp(av[1], "-d")) 
					&& (!av[2] || !av[3])){     // Throw an exception if the input or output 
						                        // names are invalid (if they are NULL).
					throw "\nERROR: wrong file name input format!\n";
				}
				else if(!strcmp(av[1], "-c") && av[2] && av[3]){ 
					Co text(av[2], av[3]);  // Constructor-initiate an instance with the valid
					                            // input and output names.
					text.compress();            // Compress the text with the compress() method.
				} 
				else if(!strcmp(av[1], "-d") && av[2] && av[3]){ 
					Dec text(av[2], av[3]); // Same as compress.
					text.decompress();
				}
				else throw "\nExceptional execution!\n";
			}
			catch(const char *e){  // This should become much more robust later on... 
				std::cout << e;
			}
			catch(...){            // Default catch statement, for posterity.
			}
		}
	}
	/* Straigh-forward implementations of printing functions. */
	void Init::print_init(void)   
	{
		std::cout << "Huffman Compressor/Decompresser            \n\n"
					 "huffman [option(s)] inputfile outputfile     \n"
					 "Type: huffman --help for more information. \n\n";
	}

	void Init::print_help(void)
	{
		print_init();
		std::cout << 
		"Ingests a file and compresses or decompresses it.\n\n"
		"Options:\n"
		"\t-c        : compresses a file using the Huffman algorithm.   \n"
		"\t-d        : decompresses a .huf file.                        \n"
		"\t--version : prints version information.                      \n"
		"\t--help    : prints this help screen.                         \n";
	}

	void Init::print_version(void)
	{
		std::cout << "Huffman Compressor/Decompresser by \n"
					 "Eudis Duran and\n"
					 "Professor George Leibman.\n"
				     "Version: "
			      << MAJ_VER  << "." << MIN_VER << "." 
			      << BUG_VER << std::endl;
	}

	int Init::get_ac(void) { return ac; }
	char** Init::get_av(void) { return av; }

}