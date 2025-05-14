#ifndef CPPFORMLANG_EPSILON_H
#define CPPFORMLANG_EPSILON_H

#include "cfg_object.h"
#include <string>
#include <functional>

namespace cppformlang {
namespace cfg {

/**
 * @brief Represents the epsilon (empty string) in a context-free grammar
 * 
 * This is the equivalent of pyformlang.cfg.epsilon.Epsilon
 */
class Epsilon : public CFGObject {
public:
    /**
     * @brief Construct a new Epsilon object
     */
    Epsilon() : CFGObject("ε") {}
    
    /**
     * @brief Get the type of the CFGObject as a string
     * @return The string "Epsilon"
     */
    std::string type() const override {
        return "Epsilon";
    }
    
    /**
     * @brief Get a string representation of epsilon
     * @return The string "ε"
     */
    std::string to_string() const override {
        return "ε";
    }
    
    /**
     * @brief Check if two Epsilon objects are equal
     * @param other The other Epsilon to compare with
     * @return Always true as all Epsilon objects are equal
     */
    bool operator==(const Epsilon&) const {
        return true;
    }
    
    /**
     * @brief Check if an Epsilon object is equal to another CFGObject
     * @param other The other CFGObject to compare with
     * @return true if other is an Epsilon, false otherwise
     */
    bool operator==(const CFGObject& other) const {
        return dynamic_cast<const Epsilon*>(&other) != nullptr;
    }
};

} // namespace cfg
} // namespace cppformlang

// Hash function for Epsilon to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::cfg::Epsilon> {
        size_t operator()(const cppformlang::cfg::Epsilon&) const {
            // All Epsilon objects are equal, so they should have the same hash
            return 0;
        }
    };
}

#endif // CPPFORMLANG_EPSILON_H