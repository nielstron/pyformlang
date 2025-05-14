#ifndef CPPFORMLANG_NONDETERMINISTIC_FINITE_AUTOMATON_H
#define CPPFORMLANG_NONDETERMINISTIC_FINITE_AUTOMATON_H

#include "finite_automaton.h"
#include "nondeterministic_transition_function.h"
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a nondeterministic finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.nondeterministic_finite_automaton.NondeterministicFiniteAutomaton
 */
class NondeterministicFiniteAutomaton : public FiniteAutomaton {
public:
    using StatePtr = std::shared_ptr<State>;
    using SymbolPtr = std::shared_ptr<Symbol>;
    using StateSet = std::unordered_set<StatePtr>;
    using SymbolSet = std::unordered_set<SymbolPtr>;
    
    /**
     * @brief Construct a new NondeterministicFiniteAutomaton
     * @param states The set of states
     * @param input_symbols The set of input symbols
     * @param transition_function The transition function
     * @param start_states The set of start states
     * @param final_states The set of final states
     */
    NondeterministicFiniteAutomaton(
        const StateSet& states = {},
        const SymbolSet& input_symbols = {},
        const std::shared_ptr<NondeterministicTransitionFunction>& transition_function = nullptr,
        const StateSet& start_states = {},
        const StateSet& final_states = {})
        : states_(states),
          input_symbols_(input_symbols),
          transition_function_(transition_function ? transition_function : std::make_shared<NondeterministicTransitionFunction>()),
          start_states_(start_states),
          final_states_(final_states) {}
    
    /**
     * @brief Check if a word is accepted by the automaton
     * @param word The word to check
     * @return true if the word is accepted, false otherwise
     */
    bool accepts(const std::vector<SymbolPtr>& word) const override {
        StateSet current_states = start_states_;
        
        for (const auto& symbol : word) {
            StateSet next_states;
            for (const auto& state : current_states) {
                auto states = transition_function_->get_next_states(state, symbol);
                next_states.insert(states.begin(), states.end());
            }
            current_states = std::move(next_states);
        }
        
        // Check if any of the current states is a final state
        for (const auto& state : current_states) {
            if (final_states_.find(state) != final_states_.end()) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Get the states of the automaton
     * @return The set of states
     */
    StateSet states() const override {
        return states_;
    }
    
    /**
     * @brief Get the input symbols of the automaton
     * @return The set of input symbols
     */
    SymbolSet input_symbols() const override {
        return input_symbols_;
    }
    
    /**
     * @brief Get the final states of the automaton
     * @return The set of final states
     */
    StateSet final_states() const override {
        return final_states_;
    }
    
    /**
     * @brief Get the start states of the automaton
     * @return The set of start states
     */
    StateSet start_states() const override {
        return start_states_;
    }
    
    /**
     * @brief Add a transition to the automaton
     * @param from_state The state to transition from
     * @param symbol The symbol to transition on
     * @param to_state The state to transition to
     */
    void add_transition(const StatePtr& from_state, const SymbolPtr& symbol, const StatePtr& to_state) {
        states_.insert(from_state);
        states_.insert(to_state);
        input_symbols_.insert(symbol);
        transition_function_->add_transition(from_state, symbol, to_state);
    }
    
    /**
     * @brief Add a start state to the automaton
     * @param state The state to add as a start state
     */
    void add_start_state(const StatePtr& state) {
        states_.insert(state);
        start_states_.insert(state);
    }
    
    /**
     * @brief Add a final state to the automaton
     * @param state The state to add as a final state
     */
    void add_final_state(const StatePtr& state) {
        states_.insert(state);
        final_states_.insert(state);
    }
    
    /**
     * @brief Check if the automaton is empty (accepts no words)
     * @return true if the automaton is empty, false otherwise
     */
    bool is_empty() const override {
        // Implementation will be added
        return true;
    }
    
    /**
     * @brief Check if the automaton accepts the empty word (epsilon)
     * @return true if the automaton accepts epsilon, false otherwise
     */
    bool accepts_epsilon() const override {
        for (const auto& state : start_states_) {
            if (final_states_.find(state) != final_states_.end()) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Get the complement of the automaton
     * @return A new automaton that is the complement of this one
     */
    std::shared_ptr<FiniteAutomaton> complement() const override {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get the union of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the union of this one and the other
     */
    std::shared_ptr<FiniteAutomaton> union_with(const std::shared_ptr<FiniteAutomaton>& other) const override {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get the intersection of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the intersection of this one and the other
     */
    std::shared_ptr<FiniteAutomaton> intersection(const std::shared_ptr<FiniteAutomaton>& other) const override {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get the concatenation of this automaton with another
     * @param other The other automaton
     * @return A new automaton that is the concatenation of this one and the other
     */
    std::shared_ptr<FiniteAutomaton> concatenate(const std::shared_ptr<FiniteAutomaton>& other) const override {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get the Kleene star of this automaton
     * @return A new automaton that is the Kleene star of this one
     */
    std::shared_ptr<FiniteAutomaton> kleene_star() const override {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Check if this automaton is equivalent to another
     * @param other The other automaton
     * @return true if they are equivalent, false otherwise
     */
    bool is_equivalent_to(const std::shared_ptr<FiniteAutomaton>& other) const override {
        // Implementation will be added
        return false;
    }
    
    /**
     * @brief Get a string representation of the automaton
     * @return A string representation
     */
    std::string to_string() const override {
        std::stringstream ss;
        
        ss << "NFA:\n";
        
        ss << "States: {";
        bool first = true;
        for (const auto& state : states_) {
            if (!first) {
                ss << ", ";
            }
            ss << state->to_string();
            first = false;
        }
        ss << "}\n";
        
        ss << "Input symbols: {";
        first = true;
        for (const auto& symbol : input_symbols_) {
            if (!first) {
                ss << ", ";
            }
            ss << symbol->to_string();
            first = false;
        }
        ss << "}\n";
        
        ss << "Start states: {";
        first = true;
        for (const auto& state : start_states_) {
            if (!first) {
                ss << ", ";
            }
            ss << state->to_string();
            first = false;
        }
        ss << "}\n";
        
        ss << "Final states: {";
        first = true;
        for (const auto& state : final_states_) {
            if (!first) {
                ss << ", ";
            }
            ss << state->to_string();
            first = false;
        }
        ss << "}\n";
        
        ss << "Transitions:\n";
        for (const auto& [from_state, symbol, to_state] : transition_function_->get_transitions()) {
            ss << "  " << from_state->to_string() << " --" << symbol->to_string() << "--> " << to_state->to_string() << "\n";
        }
        
        return ss.str();
    }

protected:
    StateSet states_;
    SymbolSet input_symbols_;
    std::shared_ptr<NondeterministicTransitionFunction> transition_function_;
    StateSet start_states_;
    StateSet final_states_;
};

} // namespace finite_automaton
} // namespace cppformlang

#endif // CPPFORMLANG_NONDETERMINISTIC_FINITE_AUTOMATON_H