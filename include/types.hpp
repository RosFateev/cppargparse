
#if !defined(ARG_TYPES_HPP)
#define ARG_TYPES_HPP

#include <type_traits>
#include <string>

namespace argparse
{
    namespace type
    {
        enum class Container_t
        {
            None,
            Vector,
            List,
            Set
        };

        enum class Primitive_t
        {
            Bool,
            Int,
            Double,
            // Currently not super needed
            String,
            CustomClass,
        };

        using type_hint = std::pair<Container_t, Primitive_t>;

        std::string str(Container_t c);
        std::string str(Primitive_t p);

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
