#include <iostream>
#include <fstream>

#include "Flp.h"

int main()
{
	std::ifstream file{ "D:/code/kaitai/flp/empty.flp" };
	std::cout << file.is_open() << std::endl;

	Flp flp{ file };
}
