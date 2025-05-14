#ifndef CPPFORMLANG_SYMBOL_H
#define CPPFORMLANG_SYMBOL_H

#include <string>
#include <functional>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a symbol in a finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.symbol.Symbol
 */
class Symbol {
public:
    /**
     * @brief Construct a new Symbol with the given value
     * @param value The string value of the symbol
     */
    explicit Symbol(std::string value) : value_(std::move(value)) {}
    
    /**
     * @brief Get the string value of the symbol
     * @return The string value
     */
    const std::string& value() const { return value_; }
    
    /**
     * @brief Check if two Symbols are equal
     * @param other The other Symbol to compare with
     * @return true if they are equal, false otherwise
     */
    bool operator==(const Symbol& other) const {
        return value_ == other.value_;
    }
    
    /**
     * @brief Check if two Symbols are not equal
     * @param other The other Symbol to compare with
     * @return true if they are not equal, false otherwise
     */
    bool operator!=(const Symbol& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Get a string representation of the symbol
     * @return A string representation
     */
    std::string to_string() const {
        return value_;
    }

private:
    std::string value_;
};

} // namespace finite_automaton
} // namespace cppformlang

// Hash function for Symbol to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::finite_automaton::Symbol> {
        size_t operator()(const cppformlang::finite_automaton::Symbol& symbol) const {
            return hash<string>()(symbol.value());
        }
    };
}

#endif // CPPFORMLANG_SYMBOL_H