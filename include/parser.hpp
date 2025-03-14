
#if !defined(ARG_PARSER_HPP)
#define ARG_PARSER_HPP

#include <string>
#include <set>
#include <map>
#include <memory>

#include "argument.hpp"

namespace argparse
{
    class Parser
    {
    public:

        Parser(const std::string& description);

        void add_argument(const Argument& arg);
        void add_argument(const Option& opt);

        void parse_args(int argc, char* argv[]);

    private:

        template<typename T>
        void add_argument_impl(const T& value,
                               std::vector<T>& container) {
            if (std::find(container.begin(),
                          container.end(),
                          value) == container.end())
            {
                container.push_back(value);
            }
        }

    public:
        std::vector<Option> optionalArgs_;
        std::vector<Argument> positionalArgs_;
        //
        std::string description_;
    };
}

#endif // !defined(ARG_PARSER_HPP)
