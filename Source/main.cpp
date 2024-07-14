#include <cassert>
#include <iostream>
#include <fstream>

#include "Flp/EventReader.h"

int main()
{
	std::ifstream file{ "D:/code/kaitai/flp/empty.flp" };
	std::cout << file.is_open() << std::endl;

	flp::EventReader flp{ file };

	return 0;

	while(flp.hasEvents())
	{
		auto e{ flp.getNextEvent() };

		switch(flp::GetEventSize(e.getType()))
		{
		case flp::EventSize::Byte:
			std::cout << e.getDataByte() << std::endl;
			break;
		case flp::EventSize::Word:
			std::cout << e.getDataWord() << std::endl;
			break;
		case flp::EventSize::Dword:
			std::cout << e.getDataDword() << std::endl;
			break;
		case flp::EventSize::Variable:
			// std::cout << e.getDataVariable() << std::endl;
			break;
		default:
			assert(false);
		}
	}
}
