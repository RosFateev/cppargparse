
#if !defined(ARG_ARGUMENT_HPP)
#define ARG_ARGUMENT_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "types.hpp"
#include "converter.hpp"


namespace argparse
{
    /// @brief Comman-line option class
    class Argument
    {
    public:
        //----------------------------------------------------------------------
        class ArgumentFmt
        {
        public:

            ArgumentFmt(const std::string& nameFlag,
                        const std::string& shortFlag = "")
                    : m_nameFlag(nameFlag),
                      m_shortFlag(shortFlag),
                      m_isOption(!nameFlag.empty() && nameFlag[0] == '-')
            {}

            inline bool operator<(const ArgumentFmt& fmt)
            {
                return m_nameFlag < fmt.m_nameFlag;
            }

            inline bool operator==(const ArgumentFmt& fmt)
            {
                return m_nameFlag == fmt.m_nameFlag;
            }

            inline bool match(const std::string& token)
            {
                return (token == m_nameFlag || token == m_shortFlag);
            }

            void DEBUG_PRINT();

            std::string m_nameFlag;
            std::string m_shortFlag;
            bool m_isOption;
        }; // ArgumentFmt

        //----------------------------------------------------------------------
        class ArgumentAction
        {
        public:
            template<typename T>
            ArgumentAction(const std::string& name,
                           T& placeholder);
                
//            template<template <typename> class C, typename T>
//            ArgumentAction(const std::string& name,
//                         C<T>& placeholderCont);

            inline void operator()(const std::string& value)
            {
                m_action(value);
            } // End: ArgumentAction::operator()

            std::string                             m_name;
        private:
            std::function<void(const std::string&)> m_action;
        };

        // TODO: is it really necessary to isolate it into ArgumentDef?
        //----------------------------------------------------------------------
        class ArgumentDef
        {
        public:

            template<typename T>
            ArgumentDef(const ArgumentFmt& format,
                        T& placeholder,
                        const std::string& actionName = "store",
                        const std::string& nargs = "0",
                        const std::string& defaultVal = "",
                        const std::vector<std::string>& choices = { "" },
                        bool isRequired = false,
                        const std::string& description = "");
            
//            template<template <typename> class C, typename T>
//            ArgumentDef(const ArgumentFmt& format,
//                        C<T>& placeholderCont,
//                        ...);

            void DEBUG_PRINT();


            ArgumentFmt                 m_format;
            ArgumentAction              m_action;
            std::string                 m_nargs;
            std::string                 m_defaultVal;
            std::vector<std::string>    m_choices;
            bool                        m_isRequired;
            std::string                 m_description;

        }; // class ArgumentDef

        Argument(const ArgumentDef& opt) : m_argumentDef(opt)
//                                           m_value(m_argumentDef.m_defaultVal)
        {}

        inline const ArgumentDef&  get_argument() const
        {
            return m_argumentDef;
        }
        
        inline ArgumentDef&  get_argument()
        {
            return m_argumentDef;
        }
//        inline const std::string&  get_value() const { return m_value; }

        void consume(std::vector<std::string>::iterator& tokenIter);

        void DEBUG_PRINT();

    private:

        ArgumentDef m_argumentDef;
//        std::string m_value;

    }; // Argument

    class ArgumentGroup
    {
    public:
        ArgumentGroup();
    
        void add_argument(std::initializer_list<Argument> argInitList);

    private:

        std::map<Argument::ArgumentFmt, Argument> args;
    };

    class MutexArgumentGroup : public ArgumentGroup
    {
    public:
        MutexArgumentGroup();
    
    private:
        Argument* m_matchedArg;
    };

} // namespace argparse


//------------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------------
namespace argparse
{
    //--------------------------------------------------------------------------
    template<typename T>
    Argument::ArgumentAction::ArgumentAction(const std::string& name,
                                             T& placeholder) : m_name("custom")
    {
        if      (name == "store")
        {
            m_action = [&](const std::string& value)
            {
                placeholder = Converter::convert<T>(value);
            };
            m_name = name;
        }
        else if (name == "count")
        {
            if constexpr (type::traits::is_incrementable<T>())
            {
                m_action = [&](const std::string& value)
                {
                    placeholder++;
                };
            }
            m_name = name;
        }
        else if (name.empty())
        {
            std::runtime_error("Error: ArgumentAction() - invalid action name!");
            m_name = "error";
        }
        else
        {
            // fallthrough so that ArgumentAction children will be able to extend
            // the functionality.
            ;
        }
    } // End: ArgumentAction::ArgumentAction()


    //--------------------------------------------------------------------------
    template<typename T>
    Argument::ArgumentDef::ArgumentDef(const ArgumentFmt& format,
                                       T& placeholder,
                                       const std::string& actionName,
                                       const std::string& nargs,
                                       const std::string& defaultVal,
                                       const std::vector<std::string>& choices,
                                       bool isRequired,
                                       const std::string& description)
        : m_format(format),
          m_action(actionName, placeholder),
          m_nargs((!nargs.empty() ? nargs
                                  : (actionName == "store" ? "?" : "0"))),
          m_defaultVal(defaultVal),
          m_choices(choices),
          m_isRequired((format.m_isOption ? isRequired : true)),
          m_description(description)
    {
        // TODO: some checks for values would be nice
    }
} // namespace argparse

#endif // !defined(ARG_ARGUMENT_HPP)
