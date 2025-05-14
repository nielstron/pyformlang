#ifndef CPPFORMLANG_EPSILON_NFA_H
#define CPPFORMLANG_EPSILON_NFA_H

#include "nondeterministic_finite_automaton.h"
#include "epsilon.h"
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a nondeterministic finite automaton with epsilon transitions
 * 
 * This is the equivalent of pyformlang.finite_automaton.epsilon_nfa.EpsilonNFA
 */
class EpsilonNFA : public NondeterministicFiniteAutomaton {
public:
    using StatePtr = std::shared_ptr<State>;
    using SymbolPtr = std::shared_ptr<Symbol>;
    using StateSet = std::unordered_set<StatePtr>;
    using SymbolSet = std::unordered_set<SymbolPtr>;
    
    /**
     * @brief Construct a new EpsilonNFA
     * @param states The set of states
     * @param input_symbols The set of input symbols
     * @param transition_function The transition function
     * @param start_states The set of start states
     * @param final_states The set of final states
     */
    EpsilonNFA(
        const StateSet& states = {},
        const SymbolSet& input_symbols = {},
        const std::shared_ptr<NondeterministicTransitionFunction>& transition_function = nullptr,
        const StateSet& start_states = {},
        const StateSet& final_states = {})
        : NondeterministicFiniteAutomaton(states, input_symbols, transition_function, start_states, final_states),
          epsilon_(std::make_shared<Epsilon>()) {}
    
    /**
     * @brief Add an epsilon transition to the automaton
     * @param from_state The state to transition from
     * @param to_state The state to transition to
     */
    void add_epsilon_transition(const StatePtr& from_state, const StatePtr& to_state) {
        states_.insert(from_state);
        states_.insert(to_state);
        transition_function_->add_transition(from_state, epsilon_, to_state);
    }
    
    /**
     * @brief Get the epsilon closure of a state
     * @param state The state to get the epsilon closure of
     * @return The set of states reachable from the given state by epsilon transitions
     */
    StateSet epsilon_closure(const StatePtr& state) const {
        // Implementation will be added
        return {state};
    }
    
    /**
     * @brief Get the epsilon closure of a set of states
     * @param states The set of states to get the epsilon closure of
     * @return The set of states reachable from the given states by epsilon transitions
     */
    StateSet epsilon_closure(const StateSet& states) const {
        // Implementation will be added
        return states;
    }
    
    /**
     * @brief Check if a word is accepted by the automaton
     * @param word The word to check
     * @return true if the word is accepted, false otherwise
     */
    bool accepts(const std::vector<SymbolPtr>& word) const override {
        // Implementation will be added
        return false;
    }
    
    /**
     * @brief Convert the epsilon-NFA to a DFA
     * @return A DFA equivalent to this epsilon-NFA
     */
    std::shared_ptr<DeterministicFiniteAutomaton> to_deterministic() const {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get a string representation of the automaton
     * @return A string representation
     */
    std::string to_string() const override {
        std::stringstream ss;
        
        ss << "Epsilon-NFA:\n";
        
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

private:
    std::shared_ptr<Epsilon> epsilon_;
};

} // namespace finite_automaton
} // namespace cppformlang

#endif // CPPFORMLANG_EPSILON_NFA_H