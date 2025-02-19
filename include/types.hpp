
#if !defined(ARG_TYPES_HPP)
#define ARG_TYPES_HPP

#include <type_traits>
#include <string>

namespace argparse
{
    namespace type
    {
        namespace traits
        {
            template <class...>
            constexpr std::false_type always_false {};

            // Type trait to allow CustomType(const std::string&) user-defined types
            template<typename T, typename = void>
            struct is_string_constructible : std::false_type
            {};

            template<typename T>
            struct is_string_constructible<T, std::void_t<decltype(T(std::declval<std::string>()))>> : std::true_type
            {};
        } // namespace traits
    } // namespace type
}

#endif // !defined(ARG_TYPES_HPP)
