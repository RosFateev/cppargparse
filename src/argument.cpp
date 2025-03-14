#include <iostream>          // std::cout
#include <algorithm>

#include "argument.hpp"


namespace argparse
{
    //--------------------------------------------------------------------------
    ArgDef::ArgCount::ArgCount(const std::string& str)
    {
        if (str == "?") 
        {
            type_ = ArgDef::ArgCount::Type::AT_MOST_ONE;
            value_ = 1;
        }
        else if (str == "*") 
        {
            type_ = ArgDef::ArgCount::Type::ANY;
            value_ = std::numeric_limits<int>::max();
        }
        else if (str == "+") 
        {
            type_ = ArgDef::ArgCount::Type::AT_LEAST_ONE;
            value_ = std::numeric_limits<int>::max();
        }
        else
        {
            try
            {
                value_ = std::stoi(str);
                type_ = Type::N;
            }
            catch (const std::invalid_argument& exc)
            {
                type_ = Type::INVALID;
                value_ = -1;
            }
        }
    }

    bool ArgDef::ArgCount::is_consumed(int consumedValCount) const
    {
        switch (type_)
        {
            case Type::ANY:
                return true;
                break;
            case Type::AT_LEAST_ONE:
                return consumedValCount > 0;
                break;
            case Type::AT_MOST_ONE:
                return consumedValCount <= 1;
                break;
            case Type::N:
                return value_ == consumedValCount;
                break;
            default:
                return false;
                break;
        }
    }

    //--------------------------------------------------------------------------
    void ArgDef::consume_values(std::vector<std::string>& tokens,
                                std::vector<std::string>::iterator& iter)
    {
        auto is_option = [](const std::string& token){
            // --foo, -f, anything else
            return (token.size() > 1 && token[0] == '-' && token[0] != '-')
                    || (token.size() > 2 && token[0] == '-' && token[0] == '-');
        };

std::cout << "consume_values(): Start\n";

        while (iter != tokens.end() && nargs_.value_ >= consumedCount_)
        {
std::cout << "consume_values(): consume iter <" << *iter << ">\n";
            if (is_option(*iter))
                break;
            if (!choices_.empty() && !matches_choices(*iter))
                break;
            exec_action(*iter);
            iter = tokens.erase(iter);
            ++consumedCount_;
        }
    }

    //--------------------------------------------------------------------------
    Argument::Argument(const std::string& name,
                       const ArgDef& def) : name_(name), ArgDef(def)
    {}

    void Argument::consume(std::vector<std::string>& tokens)
    {
        auto iter = tokens.begin();
        consume_values(tokens, iter);
    }

    //--------------------------------------------------------------------------
    Option::Option(const std::string& longFlag,
                   const std::string& shortFlag,
                   const ArgDef& def) : longFlag_(longFlag),
                                        shortFlag_(shortFlag),
                                        ArgDef(def)
    {}

    void Option::consume(std::vector<std::string>& tokens)
    {
        auto iter = tokens.begin();
        while ((iter = std::find(tokens.begin(),
                                 tokens.end(), 
                                 longFlag_))
                != tokens.end())
        {
std::cout << "found option: " << *iter << '\n';
            // boolean options hack
            exec_action("");
DEBUG_PRINT();

            iter = tokens.erase(iter);

            consume_values(tokens, iter);
        }

//        ArgAction                   action_;
//        ArgCount                    nargs_;
//        std::string                 default_;
//        std::vector<std::string>    choices_;
//        bool                        required_;
//        std::string                 description_;
//
//        int                         consumedCount_;
//        std::string                 error_;
        if (required_ && !is_consumed())
            std::cout << "Error: required, but not found\n";
    }
}
