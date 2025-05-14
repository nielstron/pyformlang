#ifndef CPPFORMLANG_STATE_H
#define CPPFORMLANG_STATE_H

#include <string>
#include <functional>

namespace cppformlang {
namespace finite_automaton {

/**
 * @brief Represents a state in a finite automaton
 * 
 * This is the equivalent of pyformlang.finite_automaton.state.State
 */
class State {
public:
    /**
     * @brief Construct a new State with the given value
     * @param value The string value of the state
     */
    explicit State(std::string value) : value_(std::move(value)) {}
    
    /**
     * @brief Get the string value of the state
     * @return The string value
     */
    const std::string& value() const { return value_; }
    
    /**
     * @brief Check if two States are equal
     * @param other The other State to compare with
     * @return true if they are equal, false otherwise
     */
    bool operator==(const State& other) const {
        return value_ == other.value_;
    }
    
    /**
     * @brief Check if two States are not equal
     * @param other The other State to compare with
     * @return true if they are not equal, false otherwise
     */
    bool operator!=(const State& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Get a string representation of the state
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

// Hash function for State to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::finite_automaton::State> {
        size_t operator()(const cppformlang::finite_automaton::State& state) const {
            return hash<string>()(state.value());
        }
    };
}

#endif // CPPFORMLANG_STATE_H