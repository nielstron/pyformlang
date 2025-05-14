#ifndef CPPFORMLANG_TERMINAL_H
#define CPPFORMLANG_TERMINAL_H

#include "cfg_object.h"
#include <string>
#include <functional>

namespace cppformlang {
namespace cfg {

/**
 * @brief Represents a terminal in a context-free grammar
 * 
 * This is the equivalent of pyformlang.cfg.terminal.Terminal
 */
class Terminal : public CFGObject {
public:
    /**
     * @brief Construct a new Terminal with the given value
     * @param value The string value of the terminal
     */
    explicit Terminal(std::string value) : CFGObject(std::move(value)) {}
    
    /**
     * @brief Get the type of the CFGObject as a string
     * @return The string "Terminal"
     */
    std::string type() const override {
        return "Terminal";
    }
    
    /**
     * @brief Get a string representation of the terminal
     * @return A string representation
     */
    std::string to_string() const override {
        return value_;
    }
};

} // namespace cfg
} // namespace cppformlang

// Hash function for Terminal to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::cfg::Terminal> {
        size_t operator()(const cppformlang::cfg::Terminal& term) const {
            return hash<string>()(term.value());
        }
    };
}

#endif // CPPFORMLANG_TERMINAL_H