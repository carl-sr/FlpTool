#include <iostream>
#include <fstream>

#include "../Ksy/Build/flp.h"



int main()
{
	std::ifstream file{ "/mnt/d/code/kaitai/flp/empty.flp" };
	// /mnt/d/code/kaitai/flp/FlpTool
	std::cout << file.is_open() << std::endl;
	kaitai::kstream inStream{ &file };
	flp_t f{ &inStream };
}
