#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "TurtleCommand.hpp"

namespace lsys
{
    class Lsystem
    {
    public:
        Lsystem();

        void evaluate(Turtle& turtle);
        void iterate(unsigned int iterations);

        const std::string& getAxiom() const;
        void setAxiom(const std::string& axiom);

        const std::string& getIteratedAxiom() const;

        const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& getSymbols() const;
        void setSymbols(const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& symbols);
        void addSymbol(char character, std::shared_ptr<TurtleCommand> turtle_command);

        const std::unordered_map<char, std::string>& getRules() const;
        void setRules(const std::unordered_map<char, std::string>& rules);
        void addRule(char character, const std::string& replacement);

    private:
        std::string axiom;
        std::string iterated_axiom;
        std::unordered_map<char, std::shared_ptr<TurtleCommand>> symbols;
        std::unordered_map<char, std::string> rules;

        bool is_iterated;
    };
}