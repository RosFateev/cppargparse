
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

        void add_argument(std::initializer_list<Argument> argInitList);
        void parse_args();
    
    // TODO:
// 1.
//   void add_argument_group();
    // RETURNS: "argumentgroup" object 
    // ARGS: title=None, description=None, *[, argument_default][, conflict_handler]
// 2.
//    void add_mutually_exclusive_group();
    // RETURNS: "exclusivegroup" obj
    // ARGS: required=False
// 3.
//    void add_subparsers();
    // RETURNS: "subparsers" object
    // ARGS: [, title][, description][, prog][, parser_class][, action][, dest][, required][, help][, metavar]


    private:

        void parse(const std::string& token);

    private:

        // TODO: these might be better placed as "defaults" for argument groups later on
        std::vector<std::unique_ptr<ArgumentGroup>>
        std::set<Option> m_options;
        std::set<Option> m_arguments;

        // TODO:
        // container of argument groups
    //    std::vector<std::set<Option>> m_argGroups;
        // container of mutually exclusive groups
    //    std::vector<std::set<Option>> m_mutExclGroups;
        // container of subparsers
    //    std::map<std::string, Parser> m_subparsers;
    };
}

#endif // !defined(ARG_PARSER_HPP)
