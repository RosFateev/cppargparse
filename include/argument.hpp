
#if !defined(ARG_ARGUMENT_HPP)
#define ARG_ARGUMENT_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iterator>
#include <limits>
#include <iostream>

#include "types.hpp"
#include "converter.hpp"


namespace argparse
{
    //--------------------------------------------------------------------------
    class ArgDef
    {
    public:
        //----------------------------------------------------------------------
        class ArgAction
        {
        public:
            template<typename T>
            ArgAction(const std::string& name,
                      T& placeholder);
                    
//            template<template <typename> class C, typename T>
//            ArgAction(const std::string& name,
//                         C<T>& placeholderCont);
    
            inline void operator()(const std::string& value)
            {
                action_(value);
            } // End: ArgAction::operator()

            std::string                             name_;
        private:
            std::function<void(const std::string&)> action_;
        }; // class ArgAction
    
        //----------------------------------------------------------------------
        class ArgCount
        {
        public:
    
            enum class Type
            {
                /// @brief Invalid number of arguments.
                INVALID         = 'E',
                /// @brief '?': 0 or 1
                AT_MOST_ONE     = '?',
                /// @brief '*': >= 0
                ANY             = '*',
                /// @brief '+': >= 1
                AT_LEAST_ONE    = '+',
                /// @brief 'N': any positive int
                N               = 'N'
            }; // enum class Type
    
            ArgCount(const std::string& str);
            
            bool is_consumed(int consumedValCount) const;
    
        public:

            Type type_;
            int value_;
        }; // class ArgCount

        //----------------------------------------------------------------------
        template<typename T>
        ArgDef(T& placeholder,
               const std::string& actionName = "store",
               const std::string& nargs = "?",
               bool required = false,
               const std::string& defaultVal = "0",
               const std::vector<std::string>& choices = { "" },
               const std::string& description = "") : action_(actionName,
                                                              placeholder),
                                                      nargs_(nargs),
                                                      required_(required),
                                                      default_(defaultVal),
                                                      choices_(choices),
                                                      description_(description),
                                                      consumedCount_(0),
                                                      error_("")
        {
            if (!default_.empty())
                // preventive measures in case option won't be consumed 
                action_(default_);
        }
                
//            template<template <typename> class C, typename T>
//            ArgDef(const ArgumentFmt& format_,
//                        C<T>& placeholderCont,
//                        ...);

//        virtual void consume(std::vector<std::string>& tokens);
//        virtual bool operator==(const ArgDef& rhs);
//        virtual bool operator<(const ArgDef& rhs);

    protected:

        inline bool is_consumed() const {
            return nargs_.is_consumed(consumedCount_);
        }

        inline bool matches_choices(const std::string& token) const {
            for (const auto& choice : choices_)
                if (token == choice)
                    return true;
            return false;
        }

        inline void exec_action(const std::string& value) {
            action_(value);
            ++consumedCount_;
        }

        void consume_values(std::vector<std::string>& tokens,
                            std::vector<std::string>::iterator& iter);

        inline void DEBUG() const
        {
            std::cout << '['
                      << "action: " << action_.name_ << "; "
                      << "nargs: (" << (char)nargs_.type_ << ", " << nargs_.value_ << "); "
                      << "default: " << default_ << "; "
                      << "required: " << (required_ ? "true" : "false") << "; "
                      << "description: " << description_ << "; "
                      << "( consumed: " << consumedCount_ << ')'
                      << "]\n";
        }

    public:
    
        ArgAction                   action_;
        ArgCount                    nargs_;
        std::string                 default_;
        std::vector<std::string>    choices_;
        bool                        required_;
        std::string                 description_;
    
    private:

        int                         consumedCount_;
        std::string                 error_;
    }; // class ArgDef

    /// @brief Comman-line option class
    class Argument : public ArgDef
    {
    public:
        //----------------------------------------------------------------------
        Argument(const std::string& name,
                 const ArgDef& def);

//        bool Argument::operator==(const std::string& str) const;
        inline bool operator==(const Argument& arg) const {
            return name_ == arg.name_;
        }
//        bool Argument::operator<(const std::string& str) const;
        inline bool operator<(const Argument& arg) const {
            return name_ < arg.name_;
        }

        //----------------------------------------------------------------------
        // ACCESSORS
        inline const std::string&  name() const { return name_; }
//        inline std::string&        name()       { return name_; }

        void consume(std::vector<std::string>& tokens);

        void help() const;

        inline void DEBUG_PRINT() const {
            std::cout << "Argument<" << name_ << "; ";
            DEBUG();
            std::cout << ">\n";
        }

    private:

        std::string     name_; // name (positional) or flags (option)
    }; // Argument


    class Option : public ArgDef
    {
    public:
        Option(const std::string& longFlag,
               const std::string& shortFlag,
               const ArgDef& def);

        bool operator==(const std::string& str) const {
            return (longFlag_ == str || shortFlag_ == str);
        }
        inline bool operator==(const Option& arg) const {
            return (longFlag_ == arg.longFlag_ && shortFlag_ == arg.shortFlag_);
        }
        bool operator<(const std::string& str) const {
            return (longFlag_ < str || shortFlag_ < str);
        }
        inline bool operator<(const Option& arg) const {
            return (longFlag_ < arg.longFlag_ || shortFlag_ < arg.shortFlag_);
        }

        void consume(std::vector<std::string>& tokens);

        //----------------------------------------------------------------------
        // ACCESSORS
        inline const std::string&  long_flag()  const { return longFlag_; }
        inline const std::string&  short_flag() const { return shortFlag_; }

        inline void DEBUG_PRINT() const {
            std::cout << "Option<" << longFlag_ << "; ";
            DEBUG();
            std::cout << ">\n";
        }

    private:

        std::string longFlag_;
        std::string shortFlag_;
    };

} // namespace argparse


//------------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------------
namespace argparse
{
    //--------------------------------------------------------------------------
    template<typename T>
    Argument::ArgAction::ArgAction(const std::string& inName,
                                   T& placeholder)
    {
        std::string finalName { inName };
        if      (inName == "store")
            // Also store_default
            action_ = [&placeholder](const std::string& value)
            {
std::cout << "action::store() with argument <" << value << ">\n";
                if (value.empty())
                {
                    if constexpr (std::is_same_v<T, bool>)
                    {
std::cout << "action::store() bool special case\n";
                        placeholder = Converter::convert<T>("1");
                    }
                }
                else
                {
std::cout << "action::store() general conversion\n";
                    placeholder = Converter::convert<T>(value);
                }                   
            };
        else if (inName == "count")
            if constexpr (type::traits::is_incrementable<T>())
                action_ = [&](const std::string& value)
                {
                    placeholder++;
                };
        else
            // fallthrough so that ArgAction children will be able to extend
            // the functionality.
            finalName = "error";
        
        name_ = finalName;
    } // End: ArgAction::ArgAction()

} // namespace argparse

#endif // !defined(ARG_ARGUMENT_HPP)
