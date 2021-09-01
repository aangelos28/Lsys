#include "Lsystem.hpp"
#include "Turtle.hpp"

namespace lsys
{
    Lsystem::Lsystem()
        : is_evaluated(false)
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

    void Lsystem::draw(Turtle& turtle)
    {
        if (!this->is_evaluated) return;

        turtle.clearCommands();
        turtle.resetTransform();

        for (char c : evaluated_axiom)
        {
            auto command = symbols[c];
            if (command == nullptr) continue;

            turtle.addCommand(command);
        }

        turtle.run();
    }

    void Lsystem::evaluate(unsigned int iterations)
    {
        if (this->is_evaluated) return;

        evaluated_axiom = axiom;

        for (unsigned int i = 0; i < iterations; ++i)
        {
            for (const auto& rule : rules)
            {
                replaceStrChar(evaluated_axiom, rule.first, rule.second);
            }
        }

        this->is_evaluated = true;
    }

    const std::string& Lsystem::getAxiom() const
    {
        return axiom;
    }

    void Lsystem::setAxiom(const std::string& axiom)
    {
        this->axiom = axiom;
        this->is_evaluated = false;
    }

    const std::string& Lsystem::getEvaluatedAxiom() const
    {
        return evaluated_axiom;
    }

    const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& Lsystem::getSymbols() const
    {
        return symbols;
    }

    void Lsystem::setSymbols(const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& symbols)
    {
        this->symbols = symbols;
        this->is_evaluated = false;
    }

    void Lsystem::addSymbol(char character, std::shared_ptr<TurtleCommand> turtle_command)
    {
        // Ensure symbol has not been already added
        if (symbols.find(character) != symbols.end()) return;

        symbols.insert({character, turtle_command});
        this->is_evaluated = false;
    }

    const std::unordered_map<char, std::string>& Lsystem::getRules() const
    {
        return rules;
    }

    void Lsystem::setRules(const std::unordered_map<char, std::string>& rules)
    {
        this->rules = rules;
        this->is_evaluated = false;
    }

    void Lsystem::addRule(char character, const std::string& replacement)
    {
        // Ensure rule has not been already added
        if (rules.find(character) != rules.end()) return;

        rules.insert({character, replacement});
        this->is_evaluated = false;
    }
}
