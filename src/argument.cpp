#include <iostream>          // std::cout

#include "argument.hpp"


namespace argparse
{
    //--------------------------------------------------------------------------
//    Argument::ArgumentFmt::ArgumentFmt(const std::string& nm,
//                                 const std::string& lFlag,
//                                 const std::string& sFlag) : name(nm),
//                                                             longFlag(lFlag),
//                                                             shortFlag(sFlag)
//    {}

    void Argument::ArgumentFmt::DEBUG_PRINT()
    {
        std::cout << "\t{\n"
                  << "\t\t name: " << name << ",\n"
                  << "\t\t longFlag: "<< longFlag << ",\n"
                  << "\t\t shortFlag: " << shortFlag << ",\n"
                  << "\t}\n";
    }

    void Argument::ArgumentDef::DEBUG_PRINT()
    {
        format.DEBUG_PRINT();
        std::cout << "\t{\n"
                  << "\t\t nargs: " << nargs << ",\n"
                  << "\t\t defaultVal: " << defaultVal << ",\n"
//                  << "\t\t type: " << type::str(type.first) << "<" << type::str(type.second) << ">,\n"
//                  << "\t\t choices: " << choices << ",\n"
                  << "\t\t isRequired: " << isRequired << ",\n"
                  << "\t\t description: " << description << ",\n"
                  << "\t}\n";
    }

    //------------------------------------------------------------------------------
    Argument::Argument(const Argument::ArgumentDef& opt) : m_argumentDef(opt),
                                                   m_value(m_argumentDef.defaultVal)
    {}

    void Argument::DEBUG_PRINT()
    {
        std::cout << "/------------------------------\\\n";
        m_argumentDef.DEBUG_PRINT();
        std::cout << "\tvalue: " << m_value << "\n";
        std::cout << "\\------------------------------/\n";
    }

}