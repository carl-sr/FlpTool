#include <cassert>
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
		auto e{ flp.getNextEvent() };

		switch(GetEventSize(e.getType()))
		{
		case FlpEventSize::Byte:
			std::cout << e.getDataByte() << std::endl;
			break;
		case FlpEventSize::Word:
			std::cout << e.getDataWord() << std::endl;
			break;
		case FlpEventSize::Dword:
			std::cout << e.getDataDword() << std::endl;
			break;
		case FlpEventSize::Variable:
			// std::cout << e.getDataVariable() << std::endl;
			break;
		default:
			assert(false);
		}
	}
}
