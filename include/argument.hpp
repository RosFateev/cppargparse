
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
                        const std::string& sFlag = "");

            bool operator<(const ArgumentFmt& fmt);
            bool operator==(const ArgumentFmt& fmt);

            bool match(const std::string& token);

            void DEBUG_PRINT();

            std::string nameFlag;
            std::string shortFlag;
            bool isOption;
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

            void operator()(const std::string& value);

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
                        const std::string& defVal = "",
                        const std::vector<std::string>& choices = { "" },
                        bool required = false,
                        const std::string& descr = "");
            
//            template<template <typename> class C, typename T>
//            ArgumentDef(const ArgumentFmt& format,
//                        C<T>& placeholderCont,
//                        ...);

            void DEBUG_PRINT();


            ArgumentFmt                 format;
            ArgumentAction              action;
            std::string                 nargs;
            std::string                 defaultVal;
            std::vector<std::string>    choices;
            bool                        isRequired;
            std::string                 description;

        }; // class ArgumentDef

        Argument(const ArgumentDef& opt);

        inline const ArgumentDef&  get_argument() const { return m_argumentDef; }
        inline ArgumentDef&  get_argument() { return m_argumentDef; }
//        inline const std::string&  get_value() const { return m_value; }

        void consume(std::vector<std::string>::iterator& tokenIter);

        void DEBUG_PRINT();

    private:

        ArgumentDef m_argumentDef;
        std::string m_value;

    }; // Argument

    class ArgumentGroup
    {
    public:
        ArgumentGroup();
    
        void add_argument(std::initializer_list<Argument> argInitList);

    private:
        // TODO: ArgumentFmt has no hash or comparison or order
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
    Argument::ArgumentFmt::ArgumentFmt(const std::string& nF,
                                       const std::string& sFlag)                 
        : nameFlag(nF),
          shortFlag(sFlag),
          isOption(!nF.empty() && nF[0] == '-')
    {}

    bool Argument::ArgumentFmt::operator<(const ArgumentFmt& fmt)
    {
        return nameFlag < fmt.nameFlag;
    }

    bool Argument::ArgumentFmt::operator==(const ArgumentFmt& fmt)
    {
        return nameFlag == fmt.nameFlag;
    }

    bool Argument::ArgumentFmt::match(const std::string& token)
    {
        return (token == nameFlag || token == shortFlag);
    }


    //--------------------------------------------------------------------------
//    template<>
//    Argument::ArgumentAction::ArgumentAction<bool>(const std::string& name,
//                                                   bool& placeholder)
//    {
//        if      (name == "store")
//        {
//            m_action = [&](const std::string& value)
//            {
//                placeholder = Converter::convert<bool>(value);
//            };
//        }
//        else if (name.empty())
//        {
//            std::runtime_error("Error: ArgumentAction() - invalid action name!");
//        }
//        else
//        {
//            // fallthrough so that ArgumentAction children will be able to extend
//            // the functionality.
//            ;
//        }
//    }

    template<typename T>
    Argument::ArgumentAction::ArgumentAction(const std::string& name,
                                             T& placeholder)
    {
        if      (name == "store")
        {
            m_action = [&](const std::string& value)
            {
                placeholder = Converter::convert<T>(value);
            };
        }
//        else if (name == "count")
//        {
//            m_action = [&](const std::string& value)
//            {
//                placeholder++;
//            };
//        }
        else if (name.empty())
        {
            std::runtime_error("Error: ArgumentAction() - invalid action name!");
        }
        else
        {
            // fallthrough so that ArgumentAction children will be able to extend
            // the functionality.
            ;
        }
    } // End: ArgumentAction::ArgumentAction()

    void Argument::ArgumentAction::operator()(const std::string& value)
    {
        m_action(value);
    } // End: ArgumentAction::operator()


    //--------------------------------------------------------------------------
    template<typename T>
    Argument::ArgumentDef::ArgumentDef(const ArgumentFmt& inFormat,
                                       T& placeholder,
                                       const std::string& actionName,
                                       const std::string& inNargs,
                                       const std::string& defVal,
                                       const std::vector<std::string>& choices,
                                       bool required,
                                       const std::string& descr)
        : format(inFormat),
          action(actionName, placeholder),
          nargs((!inNargs.empty() ? inNargs
                                  : (actionName == "store" ? "?" : "0"))),
          defaultVal(defVal),
          choices(choices),
          isRequired((format.isOption ? required : true)),
          description(descr)
    {
        // TODO: some checks for values would be nice
    }

    //--------------------------------------------------------------------------
    Argument::Argument(const ArgumentDef& opt) : m_argumentDef(opt),
                                                 m_value(m_argumentDef.defaultVal)
    {}
} // namespace argparse

#endif // !defined(ARG_ARGUMENT_HPP)
