#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "TurtleCommand.hpp"

namespace lsys
{
    /**
     * Represents an L-system (Lindenmayer system).
     * Provides a formal grammar and parallel rewriting system for turtle graphics.
     * It is possible to define a custom axiom, custom symbols, and custom rules to create a wide variety of graphics.
     */
    class Lsystem
    {
    public:
        Lsystem();

        /**
         * Draw the L-system with a turtle
         *
         * @param turtle The turtle to draw with
         */
        void draw(Turtle& turtle);

        /**
         * Evaluate the L-system for a given number of iterations.
         *
         * @param iterations Number of recursive iterations
         */
        void evaluate(unsigned int iterations);

        /**
         * Add a new symbol that maps to a given turtle command (or nullptr).
         *
         * @param character The character representing the symbol
         * @param turtle_command Turtle command to execute when symbol is encountered (or nullptr to execute no command)
         */
        void addSymbol(char character, std::shared_ptr<TurtleCommand> turtle_command);

        /**
         * Add a new rule that rewrites the given character with another string.
         *
         * @param character Character to rewrite
         * @param replacement String to write instead of the character
         */
        void addRule(char character, const std::string& replacement);

        const std::string& getAxiom() const;
        void setAxiom(const std::string& axiom);

        const std::string& getEvaluatedAxiom() const;

        const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& getSymbols() const;
        void setSymbols(const std::unordered_map<char, std::shared_ptr<TurtleCommand>>& symbols);

        const std::unordered_map<char, std::string>& getRules() const;
        void setRules(const std::unordered_map<char, std::string>& rules);

    private:
        /**
         * The initial string of the L-system.
         */
        std::string axiom;

        /**
         * The string created after evaluating the L-system.
         */
        std::string evaluated_axiom;

        /**
         * Symbols in the L-system grammar.
         * Map of characters to turtle commands.
         */
        std::unordered_map<char, std::shared_ptr<TurtleCommand>> symbols;

        /**
         * Rewriting rules of the L-system.
         * Map of characters to replacement strings.
         */
        std::unordered_map<char, std::string> rules;

        /**
         * Whether the L-system has been evaluated.
         */
        bool is_evaluated;
    };
}