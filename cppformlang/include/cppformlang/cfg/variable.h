#ifndef CPPFORMLANG_VARIABLE_H
#define CPPFORMLANG_VARIABLE_H

#include "cfg_object.h"
#include <string>
#include <functional>

namespace cppformlang {
namespace cfg {

/**
 * @brief Represents a variable in a context-free grammar
 * 
 * This is the equivalent of pyformlang.cfg.variable.Variable
 */
class Variable : public CFGObject {
public:
    /**
     * @brief Construct a new Variable with the given value
     * @param value The string value of the variable
     */
    explicit Variable(std::string value) : CFGObject(std::move(value)) {}
    
    /**
     * @brief Get the type of the CFGObject as a string
     * @return The string "Variable"
     */
    std::string type() const override {
        return "Variable";
    }
    
    /**
     * @brief Get a string representation of the variable
     * @return A string representation
     */
    std::string to_string() const override {
        return value_;
    }
};

} // namespace cfg
} // namespace cppformlang

// Hash function for Variable to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::cfg::Variable> {
        size_t operator()(const cppformlang::cfg::Variable& var) const {
            return hash<string>()(var.value());
        }
    };
}

#endif // CPPFORMLANG_VARIABLE_H