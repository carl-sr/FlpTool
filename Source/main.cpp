#include <iostream>
#include <fstream>

int main()
{
	const std::ifstream file{ "D:/code/kaitai/flp/empty.flp" };
	std::cout << file.is_open() << std::endl;

}
