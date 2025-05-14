#ifndef CPPFORMLANG_NONDETERMINISTIC_TRANSITION_FUNCTION_H
#define CPPFORMLANG_NONDETERMINISTIC_TRANSITION_FUNCTION_H

#include "state.h"
#include "symbol.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <utility>
#include <functional>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a transition function in a nondeterministic finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.nondeterministic_transition_function.NondeterministicTransitionFunction
 */
class NondeterministicTransitionFunction {
public:
    using StatePtr = std::shared_ptr<State>;
    using SymbolPtr = std::shared_ptr<Symbol>;
    using StateSet = std::unordered_set<StatePtr>;
    
    /**
     * @brief Construct a new NondeterministicTransitionFunction
     */
    NondeterministicTransitionFunction() = default;
    
    /**
     * @brief Add a transition to the function
     * @param from_state The state to transition from
     * @param symbol The symbol to transition on
     * @param to_state The state to transition to
     */
    void add_transition(const StatePtr& from_state, const SymbolPtr& symbol, const StatePtr& to_state) {
        transitions_[{from_state, symbol}].insert(to_state);
    }
    
    /**
     * @brief Get all states that can be reached from a state on a symbol
     * @param from_state The state to transition from
     * @param symbol The symbol to transition on
     * @return The set of states reached
     */
    StateSet get_next_states(const StatePtr& from_state, const SymbolPtr& symbol) const {
        auto it = transitions_.find({from_state, symbol});
        if (it != transitions_.end()) {
            return it->second;
        }
        return {};
    }
    
    /**
     * @brief Check if a transition exists
     * @param from_state The state to transition from
     * @param symbol The symbol to transition on
     * @param to_state The state to transition to
     * @return true if the transition exists, false otherwise
     */
    bool has_transition(const StatePtr& from_state, const SymbolPtr& symbol, const StatePtr& to_state) const {
        auto it = transitions_.find({from_state, symbol});
        return it != transitions_.end() && it->second.find(to_state) != it->second.end();
    }
    
    /**
     * @brief Get all transitions
     * @return A vector of transitions (from_state, symbol, to_state)
     */
    std::vector<std::tuple<StatePtr, SymbolPtr, StatePtr>> get_transitions() const {
        std::vector<std::tuple<StatePtr, SymbolPtr, StatePtr>> result;
        for (const auto& [key, to_states] : transitions_) {
            const auto& [from_state, symbol] = key;
            for (const auto& to_state : to_states) {
                result.emplace_back(from_state, symbol, to_state);
            }
        }
        return result;
    }
    
    /**
     * @brief Get all states that can be reached from a state on a symbol
     * @param from_state The state to transition from
     * @param symbol The symbol to transition on
     * @return The set of states reached
     */
    StateSet get_next_states_iterable(const StatePtr& from_state, const SymbolPtr& symbol) const {
        return get_next_states(from_state, symbol);
    }

private:
    // Custom hash function for pair of shared_ptr
    struct PairHash {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<std::shared_ptr<T1>, std::shared_ptr<T2>>& p) const {
            auto h1 = std::hash<T1>()(*p.first);
            auto h2 = std::hash<T2>()(*p.second);
            return h1 ^ (h2 << 1);
        }
    };
    
    // Custom equality function for pair of shared_ptr
    struct PairEqual {
        template <typename T1, typename T2>
        bool operator()(const std::pair<std::shared_ptr<T1>, std::shared_ptr<T2>>& p1,
                        const std::pair<std::shared_ptr<T1>, std::shared_ptr<T2>>& p2) const {
            return *p1.first == *p2.first && *p1.second == *p2.second;
        }
    };
    
    std::unordered_map<
        std::pair<StatePtr, SymbolPtr>,
        StateSet,
        PairHash,
        PairEqual
    > transitions_;
};

} // namespace finite_automaton
} // namespace cppformlang

#endif // CPPFORMLANG_NONDETERMINISTIC_TRANSITION_FUNCTION_H