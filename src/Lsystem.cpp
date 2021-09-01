#include "Lsystem.hpp"
#include "Turtle.hpp"

namespace lsys
{
    Lsystem::Lsystem()
        : is_iterated(false)
    {
    }

    void replaceStrChar(std::string& str, const char from, const std::string& to) {
        std::string::size_type n = 0;

        while ((n = str.find(from, n)) != std::string::npos)
        {
            str.replace(n, 1, to);
            n += to.size();
        }
    }

    void Lsystem::evaluate(Turtle& turtle)
    {
        if (!this->is_iterated) return;

        turtle.clearCommands();
        turtle.resetTransform();

        for (char c : iterated_axiom)
        {
            auto command = symbols[c];
            if (command == nullptr) continue;

            turtle.addCommand(command);
        }

        turtle.run();
    }

    void Lsystem::iterate(unsigned int iterations)
    {
        if (this->is_iterated) return;

        iterated_axiom = axiom;

        for (unsigned int i = 0; i < iterations; ++i)
        {
            for (const auto& rule : rules)
            {
                replaceStrChar(iterated_axiom, rule.first, rule.second);
            }
        }

        this->is_iterated = true;
    }

    const std::string& Lsystem::getAxiom() const
    {
        return axiom;
    }

    void Lsystem::setAxiom(const std::string& axiom)
    {
        this->axiom = axiom;
        this->is_iterated = false;
    }

    const std::string& Lsystem::getIteratedAxiom() const
    {
        return iterated_axiom;
    }

    const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& Lsystem::getSymbols() const
    {
        return symbols;
    }

    void Lsystem::setSymbols(const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& symbols)
    {
        this->symbols = symbols;
        this->is_iterated = false;
    }

    void Lsystem::addSymbol(char character, std::shared_ptr<TurtleCommand> turtle_command)
    {
        // Ensure symbol has not been already added
        if (symbols.find(character) != symbols.end()) return;

        symbols.insert({character, turtle_command});
        this->is_iterated = false;
    }

    const std::unordered_map<char, std::string>& Lsystem::getRules() const
    {
        return rules;
    }

    void Lsystem::setRules(const std::unordered_map<char, std::string>& rules)
    {
        this->rules = rules;
        this->is_iterated = false;
    }

    void Lsystem::addRule(char character, const std::string& replacement)
    {
        // Ensure rule has not been already added
        if (rules.find(character) != rules.end()) return;

        rules.insert({character, replacement});
        this->is_iterated = false;
    }
}
