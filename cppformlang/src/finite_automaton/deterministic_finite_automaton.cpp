#include <cppformlang/finite_automaton/deterministic_finite_automaton.h>
#include <algorithm>
#include <stdexcept>

namespace cppformlang {
namespace finite_automaton {

bool DeterministicFiniteAutomaton::accepts(const std::vector<std::string>& word) const {
    if (!start_state_) {
        return false;
    }
    
    StatePtr current_state = start_state_;
    
    for (const auto& symbol_str : word) {
        auto symbol = std::make_shared<Symbol>(symbol_str);
        current_state = transition_function_.get_next_state(current_state, symbol);
        
        if (!current_state) {
            return false;
        }
    }
    
    return final_states_.find(current_state) != final_states_.end();
}

bool DeterministicFiniteAutomaton::accepts(const std::vector<SymbolPtr>& word) const {
    if (!start_state_) {
        return false;
    }
    
    StatePtr current_state = start_state_;
    
    for (const auto& symbol : word) {
        current_state = transition_function_.get_next_state(current_state, symbol);
        
        if (!current_state) {
            return false;
        }
    }
    
    return final_states_.find(current_state) != final_states_.end();
}

} // namespace finite_automaton
} // namespace cppformlang