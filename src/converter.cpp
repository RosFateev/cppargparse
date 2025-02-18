#include <stdexcept>
#include <type_traits>

#include "converter.hpp"


namespace argparse
{
    

/*
template<>
int
Converter::convert<int>(const std::vector<std::string>& val)
{
    if (val.size() == 1)
        if (int result = std::stoi(val.back()))
           return result;
    throw std::runtime_error("Invalid value!");
}

template<>
long int
Converter::convert<long int>(const std::vector<std::string>& val)
{
    if (val.size() == 1)
        if (long int result = std::stol(val.back()))
           return result;
    throw std::runtime_error("Invalid value!");
}

template<>
long long int
Converter::convert<long long int>(const std::vector<std::string>& val)
{
    if (val.size() == 1)
        if (long long int result = std::stoll(val.back()))
           return result;
    throw std::runtime_error("Invalid value!");
}

template<>
unsigned int
Converter::convert<unsigned int>(const std::vector<std::string>& val)
{
    if (val.size() == 1)
        if (unsigned int result = std::stoul(val.back()))
           return (unsigned int)result;
    throw std::runtime_error("Invalid value!");
}

template<>
unsigned long int
Converter::convert<unsigned long>(const std::vector<std::string>& val)
{
    return std::stoul(val);
}

template<>
unsigned long long int
Converter::convert<unsigned long long>(const std::vector<std::string>& val)
{
    return std::stoull(val);
}

template<>
float
Converter::convert<float>(const std::vector<std::string>& val)
{
    return std::stof(val);
}

template<>
double
Converter::convert<double>(const std::vector<std::string>& val)
{
    return std::stod(val);
}

template<>
long double
Converter::convert<long double>(const std::vector<std::string>& val)
{
    return std::stold(val);
}




//------------------------------------------------------------------------------
/// @brief Last resort method to convert value - construct object out of it
///
/// @param[in] val String token.
///
/// @return Object of type T constructed out of provided string
///
//------------------------------------------------------------------------------
template<typename T>
T Converter::convert(const std::vector<std::string>& val)
{
    std::cout << "Primitive generalized converter for: " << val << std::endl;
    return T(val);
}
*/

//------------------------------------------------------------------------------
// 

//------------------------------------------------------------------------------
// Insert your own here:

}
