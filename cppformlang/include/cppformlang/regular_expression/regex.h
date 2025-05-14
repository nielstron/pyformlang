#ifndef CPPFORMLANG_REGEX_H
#define CPPFORMLANG_REGEX_H

#include "regex_objects.h"
#include "../finite_automaton/epsilon_nfa.h"
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

namespace cppformlang {
namespace regular_expression {

/**
 * @brief Exception thrown when a regex cannot be parsed
 */
class RegexParsingException : public std::runtime_error {
public:
    explicit RegexParsingException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Represents a regular expression
 * 
 * This is the equivalent of pyformlang.regular_expression.regex.Regex
 */
class Regex {
public:
    /**
     * @brief Construct a new Regex from a string
     * @param regex The string representation of the regex
     */
    explicit Regex(const std::string& regex);
    
    /**
     * @brief Construct a new Regex from a regex object
     * @param root The root of the regex parse tree
     */
    explicit Regex(std::shared_ptr<RegexObject> root) : root_(std::move(root)) {}
    
    /**
     * @brief Check if a word is in the language of the regex
     * @param word The word to check
     * @return true if the word is in the language, false otherwise
     */
    bool accepts(const std::vector<std::string>& word) const;
    
    /**
     * @brief Convert the regex to an epsilon-NFA
     * @return An epsilon-NFA equivalent to the regex
     */
    std::shared_ptr<finite_automaton::EpsilonNFA> to_epsilon_nfa() const;
    
    /**
     * @brief Get the union of this regex with another
     * @param other The other regex
     * @return A new regex that is the union of this one and the other
     */
    Regex union_with(const Regex& other) const;
    
    /**
     * @brief Get the concatenation of this regex with another
     * @param other The other regex
     * @return A new regex that is the concatenation of this one and the other
     */
    Regex concatenate(const Regex& other) const;
    
    /**
     * @brief Get the Kleene star of this regex
     * @return A new regex that is the Kleene star of this one
     */
    Regex kleene_star() const;
    
    /**
     * @brief Get a string representation of the regex
     * @return A string representation
     */
    std::string to_string() const {
        return root_ ? root_->to_string() : "null";
    }
    
    /**
     * @brief Get the root of the regex parse tree
     * @return The root of the parse tree
     */
    const std::shared_ptr<RegexObject>& root() const {
        return root_;
    }

private:
    std::shared_ptr<RegexObject> root_;
    
    /**
     * @brief Parse a regex string into a parse tree
     * @param regex The regex string to parse
     * @return The root of the parse tree
     */
    static std::shared_ptr<RegexObject> parse(const std::string& regex);
};

} // namespace regular_expression
} // namespace cppformlang

#endif // CPPFORMLANG_REGEX_H