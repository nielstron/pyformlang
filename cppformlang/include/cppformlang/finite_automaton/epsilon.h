#ifndef CPPFORMLANG_FA_EPSILON_H
#define CPPFORMLANG_FA_EPSILON_H

#include "symbol.h"
#include <string>
#include <functional>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents the epsilon (empty string) in a finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.epsilon.Epsilon
 */
class Epsilon : public Symbol {
public:
    /**
     * @brief Construct a new Epsilon object
     */
    Epsilon() : Symbol("ε") {}
    
    /**
     * @brief Check if two Epsilon objects are equal
     * @param other The other Epsilon to compare with
     * @return Always true as all Epsilon objects are equal
     */
    bool operator==(const Epsilon&) const {
        return true;
    }
    
    /**
     * @brief Check if an Epsilon object is equal to another Symbol
     * @param other The other Symbol to compare with
     * @return true if other is an Epsilon, false otherwise
     */
    bool operator==(const Symbol& other) const {
        return dynamic_cast<const Epsilon*>(&other) != nullptr;
    }
    
    /**
     * @brief Get a string representation of epsilon
     * @return The string "ε"
     */
    std::string to_string() const {
        return "ε";
    }
};

} // namespace finite_automaton
} // namespace cppformlang

// Hash function for Epsilon to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::finite_automaton::Epsilon> {
        size_t operator()(const cppformlang::finite_automaton::Epsilon&) const {
            // All Epsilon objects are equal, so they should have the same hash
            return 0;
        }
    };
}

#endif // CPPFORMLANG_FA_EPSILON_H