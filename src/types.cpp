#include <stdexcept>

#include "types.hpp"

namespace argparse
{
    namespace type
    {
        std::string str(Container_t c)
        {
            std::string result("");
            switch(c)
            {
                case Container_t::None:
                    break;
                case Container_t::Vector:
                    result = "vector";
                    break;
                case Container_t::List:
                    result = "list";
                    break;
                case Container_t::Set:
                    result = "set";
                    break;
                default:
                    throw std::runtime_error("Error: cannot convert Container_t to std::string");
                    break;
            }
            return result;
        }

        std::string str(Primitive_t c)
        {
            std::string result("");
            switch(c)
            {
                case Primitive_t::Bool:
                    result = "bool";
                    break;
                case Primitive_t::Int:
                    result = "int";
                    break;
                case Primitive_t::Double:
                    result = "double";
                    break;
                case Primitive_t::String:
                    result = "string";
                    break;
                case Primitive_t::CustomClass:
                    result = "custom_class";
                    break;
                default:
                    throw std::runtime_error("Error: cannot convert Primitive_t to std::string");
                    break;
            }
            return result;
        }
    } // namespace type
} // namespace argparse