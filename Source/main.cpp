#include <cassert>
#include <iostream>
#include <fstream>

#include "FlpTool/FlpTool.h"

int main()
{
    std::vector<flp::FlpToolCommand> commands
    {
        flp::FlpToolCommand::Registered,
        flp::FlpToolCommand::MainPitch,
        flp::FlpToolCommand::PluginColor,
        flp::FlpToolCommand::Version,
    };
    flp::FlpTool f{ "D:/code/kaitai/flp/FlpTool/Tests/flpbin/a.flp", commands };

    std::cout << to_string(f.m_outputJson) << std::endl;

}
