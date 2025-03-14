#include <algorithm>
#include "parser.hpp"

#include <iostream>

namespace argparse
{
    //--------------------------------------------------------------------------
    Parser::Parser(const std::string& description) : description_(description)
    { }

    void Parser::add_argument(const Argument& arg)
    {
std::cout << "add_argument(Argument): <" << arg.name() << ">\n";
        add_argument_impl(arg, positionalArgs_);
    }
    void Parser::add_argument(const Option& opt)
    {
std::cout << "add_argument(Option): <" << opt.long_flag() << ">\n";
        add_argument_impl(opt, optionalArgs_);
    }

    void Parser::parse_args(int argc, char* argv[])
    {
        std::vector<std::string> tokens;
        for (int idx = 0; idx < argc; ++idx)
            tokens.push_back(std::string(argv[idx]));

        for (auto& opt : optionalArgs_)
        {
std::cout << "Option <" << opt.long_flag() << "> is being consumed\n";
            opt.consume(tokens);
opt.DEBUG_PRINT();
        }

        for (auto& posArg : positionalArgs_)
        {
std::cout << "Positional <" << posArg.name() << "> is being consumed\n";
            posArg.consume(tokens);
        }
    }

    //--------------------------------------------------------------------------
}
