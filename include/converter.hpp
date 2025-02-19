
#if !defined(ARG_CONVERTER_HPP)
#define ARG_CONVERTER_HPP

#include <string>
#include <stdexcept>
#include <cstdint>
#include <vector>

#include "types.hpp"

namespace argparse
{
    class Converter
    {
    public:

        template<typename T>
        static T convert(const std::string& value)
        {
            if (value.empty())
            {
                return T{};
            }
            if      constexpr (std::is_same_v<T, std::string>)
            {
                return value;
            }
            else if constexpr (std::is_same_v<T, bool>)
            {
                return value == "1" || value == "true";
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                return std::stof(value);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                return std::stod(value);
            }
//            else if constexpr (std::is_same_v<T, char>)
//            {
//                return static_cast<char>(value[0]);
//            }
//            else if constexpr (std::is_same_v<T, unsigned char>)
//            {
//                return static_cast<unsigned char>(value[0]);
//            }
            else if constexpr (std::is_same_v<T, int>)
            {
                return std::stoi(value);
            }
            else if constexpr (std::is_same_v<T, unsigned int>)
            {
                return unsigned(std::stoul(value));
            }
            else if constexpr (std::is_same_v<T, long int>)
            {
                return std::stoll(value);
            }
            else if constexpr (std::is_same_v<T, unsigned long int>)
            {
                return std::stoull(value);
            }
            else if constexpr (type::traits::is_string_constructible<T>())
            {
                return T(value);
            }
            // TODO: this has to be handled on ArgumentAction level through different constructor -
            // no complex nested types supported (like vect<vect<str>>)
//            else if constexpr (std::is_same_v<T, std::vector<int>>)
//            {
//                std::vector<int> result;
//                size_t posS = 0;
//                size_t posE = 0;
//                while ((posE = value.find(" ", posS)) != std::string::npos)
//                {
//                    result.push_back(std::stoi(value.substr(posS, posE)));
//                    posS = posE + 1;
//                }
//                return result;
//            }
            else
            {
                static_assert(type::traits::always_false<T>, "Unsupported type");
            }
        }
    };
}


#endif // !defined(ARG_CONVERTER_HPP)
