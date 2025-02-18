
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

            ArgumentFmt(const std::string& nm,
                        const std::string& lFlag = "",
                        const std::string& sFlag = "");

            bool match(const std::string& token);

            void DEBUG_PRINT();

            std::string name;
            std::string longFlag;
            std::string shortFlag;
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
                        const std::string& actName,
                        const std::string& nargs = "0",
                        const std::string& defVal = "",
                        const std::vector<std::string>& choices = { "" },
                        bool required = false,
                        const std::string& descr = "");
            
//            template<template <typename> class C, typename T>
//            void setter(const std::string& value, C<T>& container)

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
        inline const std::string&  get_value() const { return m_value; }

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
    Argument::ArgumentFmt::ArgumentFmt(const std::string& nm,
                                 const std::string& lFlag = "",
                                 const std::string& sFlag = "")                 
        : name(nm),
          longFlag(lFlag),
          shortFlag(sFlag)
    {}

    bool Argument::ArgumentFmt::match(const std::string& token)
    {
        return (token == name || token == longFlag || token == shortFlag);
    }


    //--------------------------------------------------------------------------
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
        else if (name == "count")
        {
            m_action = [&](const std::string& value)
            {
                placeholder++;
            };
        }
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
    Argument::ArgumentDef::ArgumentDef(const ArgumentFmt& fmt,
                                 T& placeholder,
                                 const std::string& action,
                                 const std::string& nargs,
                                 const std::string& defVal,
                                 const std::vector<std::string>& choices,
                                 bool required,
                                 const std::string& descr)
        : format(fmt),
          action(action, placeholder),
          nargs(nargs),
          defaultVal(defVal),
          choices(choices),
          isRequired(required),
          description(descr)
    {
        // TODO: some checks for values would be nice
    }
} // namespace argparse

#endif // !defined(ARG_ARGUMENT_HPP)
