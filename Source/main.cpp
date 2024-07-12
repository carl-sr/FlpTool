#include <iostream>
#include <fstream>

#include "Flp.h"

int main()
{
	std::ifstream file{ "D:/code/kaitai/flp/empty.flp" };
	std::cout << file.is_open() << std::endl;

	Flp flp{ file };

	while(flp.hasEvents())
	{
		std::cout << (std::uint8_t)flp.getNextEvent().getType() << std::endl;
	}

}
