#include <iostream>
#include <string>

#include "cxxopts.hpp"

using namespace std;

int main(int argc, char** argv)
{
    cxxopts::Options cliopt("FrenzykvOnWireServer", "A Frenzykv service wrapper.");
    cliopt.add_options()
        ("d,debug", "Enable debugging messages", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print usage")
        ("rootpath", "Working root path", cxxopts::value<::std::string>()->default_value("/tmp/frenzykv-server"))
        ;
    auto cliopt_parse_result = cliopt.parse(argc, argv);
    if (cliopt_parse_result.count("help"))
    {
        std::cout << cliopt.help() << std::endl;
        exit(0);
    }

    return 0;
}
