#include <iostream>
#include <vector>
#include <string>

#include "argument.hpp"
#include "converter.hpp"



int main()
{
    bool boolVal = false;
    argparse::Argument boolOpt(
        {
            { "--recursive" },
            boolVal,
            "store",
            "0",
            "false",
            { },
            false,
            "The program will run in a recursive mode"
        });
    boolOpt.get_argument().action("true");
    boolOpt.DEBUG_PRINT();
    std::cout << "extracted boolVal: " << boolVal << '\n';

    int intVal = 0;
    argparse::Argument intOpt(
        {
            { "iteration_count" },
            intVal
        });
    intOpt.get_argument().action("100");
    intOpt.DEBUG_PRINT();
    std::cout << "extracted value: " << boolVal << '\n';

//    std::vector<std::string> filesPlaceholder;
//    argparse::Argument vectIntOpt(
//        {
//            { "files" },
//            filesPlaceholder,
//            "append"
//            "*",
//            "foo.txt biz.txt bar.txt",
//            { },
//            false,
//            "List of files for the command to process"
//        });
//    vectIntOpt.get_argument().action("blah.json bue.xml");
//    vectIntOpt.DEBUG_PRINT();
//
//    std::cout << "extracted files:\n";
//    for (auto& item : filesPlaceholder)
//        std::cout << item << '\n';

}