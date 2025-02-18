#include <iostream>
#include <vector>
#include <string>

#include "option.hpp"
#include "converter.hpp"



int main()
{
    std::vector<int> intVect = { 1, 2, 4 };
    std::vector<std::string> strVect = { "one", "two", "four"};
    std::vector<char> charVect = { 'o', 't', 'f' };

//    argparse::Option myOpt({"custom"});
    bool boolVal;
    argparse::Option boolOpt(
        {
            { "recursive", "--recursive" },
            boolVal,
            "0",
            "false",
//        { argparse::type::Container_t::None,
//          argparse::type::Primitive_t::Bool },
            { },
            false,
            "The program will run in a recursive mode"
        });
    boolOpt.get_option().action("true");
    boolOpt.DEBUG_PRINT();
    std::cout << "extracted value: " << boolVal << '\n';

    std::vector<int> filesPlaceholder;
    argparse::Option vectIntOpt(
        {
            { "files" },
            filesPlaceholder,
            "*",
            "foo.txt biz.txt bar.txt",
            { },
            false,
            "List of files for the command to process"
        });
    vectIntOpt.get_option().action("14 88 228");
    vectIntOpt.DEBUG_PRINT();

    std::cout << "extracted files:\n";
    for (auto& item : filesPlaceholder)
        std::cout << item << '\n';

}