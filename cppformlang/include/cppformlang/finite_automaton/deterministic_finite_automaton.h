#ifndef CPPFORMLANG_DETERMINISTIC_FINITE_AUTOMATON_H
#define CPPFORMLANG_DETERMINISTIC_FINITE_AUTOMATON_H

#include "nondeterministic_finite_automaton.h"
#include "transition_function.h"
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a deterministic finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.deterministic_finite_automaton.DeterministicFiniteAutomaton
 */
class DeterministicFiniteAutomaton : public NondeterministicFiniteAutomaton {
public:
    using StatePtr = std::shared_ptr<State>;
    using SymbolPtr = std::shared_ptr<Symbol>;
    using StateSet = std::unordered_set<StatePtr>;
    using SymbolSet = std::unordered_set<SymbolPtr>;
    
    /**
     * @brief Construct a new DeterministicFiniteAutomaton
     * @param states The set of states
     * @param input_symbols The set of input symbols
     * @param transition_function The transition function
     * @param start_state The start state
     * @param final_states The set of final states
     */
    DeterministicFiniteAutomaton(
        const StateSet& states = {},
        const SymbolSet& input_symbols = {},
        const std::shared_ptr<TransitionFunction>& transition_function = nullptr,
        const StatePtr& start_state = nullptr,
        const StateSet& final_states = {})
        : NondeterministicFiniteAutomaton(states, input_symbols, nullptr, {}, final_states),
          transition_function_dfa_(transition_function ? transition_function : std::make_shared<TransitionFunction>()) {
        if (start_state) {
            start_states_.insert(start_state);
            states_.insert(start_state);
        }
    }
    
    /**
     * @brief Check if a word is accepted by the automaton
     * @param word The word to check
     * @return true if the word is accepted, false otherwise
     */
    bool accepts(const std::vector<SymbolPtr>& word) const override {
        if (start_states_.empty()) {
            return false;
        }
        
        // DFA has exactly one start state
        StatePtr current_state = *start_states_.begin();
        
        for (const auto& symbol : word) {
            current_state = transition_function_dfa_->get_next_state(current_state, symbol);
            if (!current_state) {
                return false;
            }
        }
        
        return final_states_.find(current_state) != final_states_.end();
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
        transition_function_dfa_->add_transition(from_state, symbol, to_state);
    }
    
    /**
     * @brief Set the start state of the automaton
     * @param state The state to set as the start state
     */
    void set_start_state(const StatePtr& state) {
        states_.insert(state);
        start_states_.clear();
        start_states_.insert(state);
    }
    
    /**
     * @brief Get the start state of the automaton
     * @return The start state, or nullptr if none is set
     */
    StatePtr start_state() const {
        return start_states_.empty() ? nullptr : *start_states_.begin();
    }
    
    /**
     * @brief Check if the automaton is complete (has a transition for every state and symbol)
     * @return true if the automaton is complete, false otherwise
     */
    bool is_complete() const {
        for (const auto& state : states_) {
            for (const auto& symbol : input_symbols_) {
                if (!transition_function_dfa_->get_next_state(state, symbol)) {
                    return false;
                }
            }
        }
        return true;
    }
    
    /**
     * @brief Complete the automaton by adding a sink state and transitions to it
     * @return A new automaton that is complete
     */
    std::shared_ptr<DeterministicFiniteAutomaton> make_complete() const {
        if (is_complete()) {
            return std::make_shared<DeterministicFiniteAutomaton>(*this);
        }
        
        auto result = std::make_shared<DeterministicFiniteAutomaton>(*this);
        auto sink_state = std::make_shared<State>("sink");
        result->states_.insert(sink_state);
        
        for (const auto& state : result->states_) {
            for (const auto& symbol : result->input_symbols_) {
                if (!result->transition_function_dfa_->get_next_state(state, symbol)) {
                    result->transition_function_dfa_->add_transition(state, symbol, sink_state);
                }
            }
        }
        
        // Add self-loops for the sink state
        for (const auto& symbol : result->input_symbols_) {
            result->transition_function_dfa_->add_transition(sink_state, symbol, sink_state);
        }
        
        return result;
    }
    
    /**
     * @brief Get the complement of the automaton
     * @return A new automaton that is the complement of this one
     */
    std::shared_ptr<FiniteAutomaton> complement() const override {
        auto complete_dfa = make_complete();
        auto result = std::make_shared<DeterministicFiniteAutomaton>(
            complete_dfa->states_,
            complete_dfa->input_symbols_,
            complete_dfa->transition_function_dfa_,
            complete_dfa->start_state()
        );
        
        // Complement the final states
        for (const auto& state : complete_dfa->states_) {
            if (complete_dfa->final_states_.find(state) == complete_dfa->final_states_.end()) {
                result->add_final_state(state);
            }
        }
        
        return result;
    }
    
    /**
     * @brief Minimize the automaton using Hopcroft's algorithm
     * @return A new automaton that is minimal and equivalent to this one
     */
    std::shared_ptr<DeterministicFiniteAutomaton> minimize() const {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get a string representation of the automaton
     * @return A string representation
     */
    std::string to_string() const override {
        std::stringstream ss;
        
        ss << "DFA:\n";
        
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
        
        if (!start_states_.empty()) {
            ss << "Start state: " << (*start_states_.begin())->to_string() << "\n";
        } else {
            ss << "Start state: None\n";
        }
        
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
        for (const auto& [from_state, symbol, to_state] : transition_function_dfa_->get_transitions()) {
            ss << "  " << from_state->to_string() << " --" << symbol->to_string() << "--> " << to_state->to_string() << "\n";
        }
        
        return ss.str();
    }

private:
    std::shared_ptr<TransitionFunction> transition_function_dfa_;
};

} // namespace finite_automaton
} // namespace cppformlang

#endif // CPPFORMLANG_DETERMINISTIC_FINITE_AUTOMATON_H