#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "argument.hpp"
#include "converter.hpp"
#include "parser.hpp"


//------------------------------------------------------------------------------
// SUPPORT - REMOVE
class MyPath
{
public:
    MyPath() {}
    MyPath(const std::string& path) : m_path(path) {}
    void operator=(const std::string& path) { m_path = path; }

    std::string m_path;
};

template<typename T>
void print_container(const std::vector<T>& c)
{
    std::for_each(c.cbegin(), c.cend(), [](const auto& arg){
        arg.DEBUG_PRINT();
    });
}
//------------------------------------------------------------------------------

int main()
{
    // For now no real input
    int argc = 4;
    char* argv[] = {
        "--recursive",
        "14",
        "--file-path",
        "/home/catdev/Documents"
    };

    argparse::Parser myParser { "Test parser" };
    // Bool
    bool boolVal = false;
    myParser.add_argument(
        {
            "--recursive",
            "-r",
            {
                boolVal,
                "store",
                "0",
                false,
                "false",
                { },
                "The program will run in a recursive mode"
            }
        }
    );
    // Int
    int intVal = 0;
    myParser.add_argument(
        {
            "iteration-count",
            {
                intVal
            }
        }
    );
//    // MyPath
//    MyPath pathVal;
//    myParser.add_argument(
//        "--file-path",
//        {
//            pathVal,
//            "store",
//            "1"
//        }
//    );

    std::cout << "-------------------------------------------------\n";
    print_container(myParser.optionalArgs_);
    print_container(myParser.positionalArgs_);
    std::cout << "-------------------------------------------------\n";
    myParser.parse_args(argc, argv);

    std::cout << "extracted boolVal: " << boolVal << '\n';
    std::cout << "extracted intValue: " << intVal << '\n';
//    std::cout << "extracted pathValue: " << pathVal.m_path << '\n';

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