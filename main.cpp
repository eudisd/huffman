#include "init.h"

int main(int argc, char *argv[])
{
	using namespace huffman;

	Init Main(argc, argv);
	Main.start();
	return EXIT_SUCCESS;
}