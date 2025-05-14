#ifndef CPPFORMLANG_FINITE_AUTOMATON_H
#define CPPFORMLANG_FINITE_AUTOMATON_H

#include "state.h"
#include "symbol.h"
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Base class for all finite automata
 * 
 * This is the equivalent of pyformlang.finite_automaton.finite_automaton.FiniteAutomaton
 */
class FiniteAutomaton {
public:
    using StatePtr = std::shared_ptr<State>;
    using SymbolPtr = std::shared_ptr<Symbol>;
    using StateSet = std::unordered_set<StatePtr>;
    using SymbolSet = std::unordered_set<SymbolPtr>;
    
    /**
     * @brief Virtual destructor for polymorphic behavior
     */
    virtual ~FiniteAutomaton() = default;
    
    /**
     * @brief Check if a word is accepted by the automaton
     * @param word The word to check
     * @return true if the word is accepted, false otherwise
     */
    virtual bool accepts(const std::vector<SymbolPtr>& word) const = 0;
    
    /**
     * @brief Check if a word is accepted by the automaton
     * @param word The word to check as a vector of strings
     * @return true if the word is accepted, false otherwise
     */
    virtual bool accepts(const std::vector<std::string>& word) const {
        std::vector<SymbolPtr> symbol_word;
        for (const auto& symbol_str : word) {
            symbol_word.push_back(std::make_shared<Symbol>(symbol_str));
        }
        return accepts(symbol_word);
    }
    
    /**
     * @brief Get the states of the automaton
     * @return The set of states
     */
    virtual StateSet states() const = 0;
    
    /**
     * @brief Get the input symbols of the automaton
     * @return The set of input symbols
     */
    virtual SymbolSet input_symbols() const = 0;
    
    /**
     * @brief Get the final states of the automaton
     * @return The set of final states
     */
    virtual StateSet final_states() const = 0;
    
    /**
     * @brief Get the start states of the automaton
     * @return The set of start states
     */
    virtual StateSet start_states() const = 0;
    
    /**
     * @brief Check if the automaton is empty (accepts no words)
     * @return true if the automaton is empty, false otherwise
     */
    virtual bool is_empty() const = 0;
    
    /**
     * @brief Check if the automaton accepts the empty word (epsilon)
     * @return true if the automaton accepts epsilon, false otherwise
     */
    virtual bool accepts_epsilon() const = 0;
    
    /**
     * @brief Get the complement of the automaton
     * @return A new automaton that is the complement of this one
     */
    virtual std::shared_ptr<FiniteAutomaton> complement() const = 0;
    
    /**
     * @brief Get the union of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the union of this one and the other
     */
    virtual std::shared_ptr<FiniteAutomaton> union_with(const std::shared_ptr<FiniteAutomaton>& other) const = 0;
    
    /**
     * @brief Get the intersection of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the intersection of this one and the other
     */
    virtual std::shared_ptr<FiniteAutomaton> intersection(const std::shared_ptr<FiniteAutomaton>& other) const = 0;
    
    /**
     * @brief Get the concatenation of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the concatenation of this one and the other
     */
    virtual std::shared_ptr<FiniteAutomaton> concatenate(const std::shared_ptr<FiniteAutomaton>& other) const = 0;
    
    /**
     * @brief Get the Kleene star of this automaton
     * @return A new automaton that is the Kleene star of this one
     */
    virtual std::shared_ptr<FiniteAutomaton> kleene_star() const = 0;
    
    /**
     * @brief Check if this automaton is equivalent to another
     * @param other The other automaton
     * @return true if they are equivalent, false otherwise
     */
    virtual bool is_equivalent_to(const std::shared_ptr<FiniteAutomaton>& other) const = 0;
    
    /**
     * @brief Get a string representation of the automaton
     * @return A string representation
     */
    virtual std::string to_string() const = 0;
};

} // namespace finite_automaton
} // namespace cppformlang

#endif // CPPFORMLANG_FINITE_AUTOMATON_H