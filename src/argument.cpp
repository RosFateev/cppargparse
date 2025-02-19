#include <iostream>          // std::cout

#include "argument.hpp"


namespace argparse
{
    //--------------------------------------------------------------------------
    // HELPERS
    void Argument::ArgumentFmt::DEBUG_PRINT()
    {
        std::cout << "\t{\n"
                  << "\t\t name/flag: " << m_nameFlag << ",\n"
                  << "\t\t shortFlag: "<< m_shortFlag << ",\n"
                  << "\t\t isOption: " << (m_isOption ? "true" : "false") << ",\n"
                  << "\t}\n";
    }

    void Argument::ArgumentDef::DEBUG_PRINT()
    {
        m_format.DEBUG_PRINT();
        std::cout << "\t{\n"
                  << "\t\t nargs: " << m_nargs << ",\n"
                  << "\t\t defaultVal: " << m_defaultVal << ",\n"
                  << "\t\t action: " << m_action.m_name << ",\n"
                  << "\t\t isRequired: " << (m_isRequired ? "true" : "false") << ",\n"
                  << "\t\t description: " << m_description << ",\n"
                  << "\t}\n";
    }

    void Argument::DEBUG_PRINT()
    {
        std::cout << "/------------------------------\\\n";
        m_argumentDef.DEBUG_PRINT();
//        std::cout << "\tvalue: " << m_value << "\n";
        std::cout << "\\------------------------------/\n";
    }

}