
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
            else if constexpr (std::is_same_v<T, int8_t>)
            {
                return int8_t(std::stoi(value));
            }
            else if constexpr (std::is_same_v<T, uint8_t>)
            {
                return uint8_t(std::stoul(value));
            }
            else if constexpr (std::is_same_v<T, int16_t>)
            {
                return int16_t(std::stoi(value));
            }
            else if constexpr (std::is_same_v<T, uint16_t>)
            {
                return uint16_t(std::stoul(value));
            }
            else if constexpr (std::is_same_v<T, int32_t>)
            {
                return int32_t(std::stoi(value));
            }
            else if constexpr (std::is_same_v<T, uint32_t>)
            {
                return uint32_t(std::stoul(value));
            }
            else if constexpr (std::is_same_v<T, int64_t>)
            {
                return std::stoll(value);
            }
            else if constexpr (std::is_same_v<T, uint64_t>)
            {
                return std::stoull(value);
            }
            else if constexpr (std::is_same_v<T, unsigned char>)
            {
                return static_cast<unsigned char>(value[0]);
            }
            // suppose we have a more complex type
            else if constexpr (std::is_same_v<T, std::vector<int>>)
            {
                std::vector<int> result;
                size_t posS = 0;
                size_t posE = 0;
                while ((posE = value.find(" ", posS)) != std::string::npos)
                {
                    result.push_back(std::stoi(value.substr(posS, posE)));
                    posS = posE + 1;
                }
                return result;
            }
            else
            {
                static_assert(type::traits::always_false<T>, "Unsupported type");
            }
        }
    };

/*
        template<typename T, typename VT>
        static T convert(const VT& value)
        {
            if constexpr (std::is_constructible_v<std::string, VT>)
            {
                std::string string(value);
                if (string.empty()) {
                    return T{};
                }
                if constexpr (std::is_same_v<T, std::string>) {
                    return string;
                } else if constexpr (std::is_same_v<T, bool>) {
                    return string == "1" || string == "true";
                } else if constexpr (std::is_same_v<T, float>) {
                    return std::stof(string);
                } else if constexpr (std::is_same_v<T, double>) {
                    return std::stod(string);
                } else if constexpr (std::is_same_v<T, int8_t>) {
                    return int8_t(std::stoi(string));
                } else if constexpr (std::is_same_v<T, uint8_t>) {
                    return uint8_t(std::stoul(string));
                } else if constexpr (std::is_same_v<T, int16_t>) {
                    return int16_t(std::stoi(string));
                } else if constexpr (std::is_same_v<T, uint16_t>) {
                    return uint16_t(std::stoul(string));
                } else if constexpr (std::is_same_v<T, int32_t>) {
                    return int32_t(std::stoi(string));
                } else if constexpr (std::is_same_v<T, uint32_t>) {
                    return uint32_t(std::stoul(string));
                } else if constexpr (std::is_same_v<T, int64_t>) {
                    return std::stoll(string);
                } else if constexpr (std::is_same_v<T, uint64_t>) {
                    return std::stoull(string);
                } else if constexpr (std::is_same_v<T, unsigned char>) {
                    return static_cast<unsigned char>(string[0]);
                } else {
                    static_assert(fty::always_false<T>, "Unsupported type"); // TODO: CHANGE
                }
            } else if constexpr (std::is_same_v<T, std::string>) {
                if constexpr (std::is_integral_v<VT> && !std::is_same_v<bool, VT>) {
                    return std::to_string(value);
                } else if constexpr (std::is_floating_point_v<VT>) {
                    // In case of floats std::to_string gives not pretty results. So, just use stringstream here.
                    std::stringstream ss;
                    ss << value;
                    return ss.str();
                } else if constexpr (std::is_same_v<bool, VT>) {
                    return value ? "true" : "false";
                } else {
                    static_assert(fty::always_false<T>, "Unsupported type"); // TODO: CHANGE
                }
            } else {
                return static_cast<T>(value);
            }
        } 
*/
}


#endif // !defined(ARG_CONVERTER_HPP)
