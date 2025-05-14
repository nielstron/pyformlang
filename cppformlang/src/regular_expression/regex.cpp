#include "../../include/cppformlang/regular_expression/regex.h"
#include "../../include/cppformlang/finite_automaton/epsilon_nfa.h"
#include <stack>
#include <stdexcept>

namespace cppformlang {
namespace regular_expression {

Regex::Regex(const std::string& regex) : root_(parse(regex)) {}

bool Regex::accepts(const std::vector<std::string>& word) const {
    // Convert to epsilon-NFA and check if it accepts the word
    auto enfa = to_epsilon_nfa();
    return enfa->accepts(word);
}

std::shared_ptr<finite_automaton::EpsilonNFA> Regex::to_epsilon_nfa() const {
    // This is a placeholder implementation
    // The actual implementation would convert the regex to an epsilon-NFA
    return std::make_shared<finite_automaton::EpsilonNFA>();
}

Regex Regex::union_with(const Regex& other) const {
    auto new_root = std::make_shared<Union>(root_, other.root_);
    return Regex(new_root);
}

Regex Regex::concatenate(const Regex& other) const {
    auto new_root = std::make_shared<Concatenation>(root_, other.root_);
    return Regex(new_root);
}

Regex Regex::kleene_star() const {
    auto new_root = std::make_shared<KleeneStar>(root_);
    return Regex(new_root);
}

std::shared_ptr<RegexObject> Regex::parse(const std::string& regex) {
    // This is a placeholder implementation
    // The actual implementation would parse the regex string into a parse tree
    if (regex.empty()) {
        return std::make_shared<Epsilon>();
    }
    
    // For now, just create a symbol for the first character
    return std::make_shared<Symbol>(regex.substr(0, 1));
}

} // namespace regular_expression
} // namespace cppformlang