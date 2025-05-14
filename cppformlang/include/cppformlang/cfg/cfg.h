#ifndef CPPFORMLANG_CFG_H
#define CPPFORMLANG_CFG_H

#include "variable.h"
#include "terminal.h"
#include "epsilon.h"
#include "production.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <optional>

namespace cppformlang {
namespace cfg {

/**
 * @brief Exception thrown when a string cannot be parsed by the grammar
 */
class NotParsableException : public std::runtime_error {
public:
    explicit NotParsableException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Represents a context-free grammar
 * 
 * This is the equivalent of pyformlang.cfg.cfg.CFG
 */
class CFG {
public:
    using CFGObjectPtr = std::shared_ptr<CFGObject>;
    using VariablePtr = std::shared_ptr<Variable>;
    using TerminalPtr = std::shared_ptr<Terminal>;
    using ProductionPtr = std::shared_ptr<Production>;
    using VariableSet = std::unordered_set<VariablePtr>;
    using TerminalSet = std::unordered_set<TerminalPtr>;
    using ProductionSet = std::unordered_set<ProductionPtr>;
    
    /**
     * @brief Construct a new CFG
     * @param variables The set of variables
     * @param terminals The set of terminals
     * @param start_symbol The start symbol
     * @param productions The set of productions
     */
    CFG(const VariableSet& variables = {},
        const TerminalSet& terminals = {},
        const VariablePtr& start_symbol = nullptr,
        const ProductionSet& productions = {})
        : variables_(variables),
          terminals_(terminals),
          start_symbol_(start_symbol),
          productions_(productions),
          normal_form_(nullptr),
          generating_symbols_(std::nullopt),
          nullable_symbols_(std::nullopt) {
        
        // Add start symbol to variables if it's not null
        if (start_symbol_) {
            variables_.insert(start_symbol_);
        }
        
        // Initialize productions in CFG
        for (const auto& production : productions_) {
            initialize_production_in_cfg(production);
        }
    }
    
    /**
     * @brief Get the variables of the CFG
     * @return The set of variables
     */
    const VariableSet& variables() const {
        return variables_;
    }
    
    /**
     * @brief Get the terminals of the CFG
     * @return The set of terminals
     */
    const TerminalSet& terminals() const {
        return terminals_;
    }
    
    /**
     * @brief Get the start symbol of the CFG
     * @return The start symbol
     */
    const VariablePtr& start_symbol() const {
        return start_symbol_;
    }
    
    /**
     * @brief Get the productions of the CFG
     * @return The set of productions
     */
    const ProductionSet& productions() const {
        return productions_;
    }
    
    /**
     * @brief Get the generating symbols of the CFG
     * @return The set of generating symbols
     */
    std::unordered_set<CFGObjectPtr> get_generating_symbols() {
        if (!generating_symbols_) {
            generating_symbols_ = get_generating_or_nullable(false);
        }
        return *generating_symbols_;
    }
    
    /**
     * @brief Get the nullable symbols of the CFG
     * @return The set of nullable symbols
     */
    std::unordered_set<CFGObjectPtr> get_nullable_symbols() {
        if (!nullable_symbols_) {
            nullable_symbols_ = get_generating_or_nullable(true);
        }
        return *nullable_symbols_;
    }
    
    /**
     * @brief Check if the CFG generates the empty string (epsilon)
     * @return true if the CFG generates epsilon, false otherwise
     */
    bool generate_epsilon() {
        // Implementation will be added
        return false;
    }
    
    /**
     * @brief Get the reachable symbols of the CFG
     * @return The set of reachable symbols
     */
    std::unordered_set<CFGObjectPtr> get_reachable_symbols() {
        // Implementation will be added
        return {};
    }
    
    /**
     * @brief Remove useless symbols from the CFG
     * @return A new CFG without useless symbols
     */
    std::shared_ptr<CFG> remove_useless_symbols() {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Remove epsilon productions from the CFG
     * @return A new CFG without epsilon productions
     */
    std::shared_ptr<CFG> remove_epsilon() {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Get the unit pairs of the CFG
     * @return The set of unit pairs
     */
    std::unordered_set<std::pair<VariablePtr, VariablePtr>> get_unit_pairs() {
        // Implementation will be added
        return {};
    }
    
    /**
     * @brief Eliminate unit productions from the CFG
     * @return A new CFG without unit productions
     */
    std::shared_ptr<CFG> eliminate_unit_productions() {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Convert the CFG to Chomsky Normal Form
     * @return A new CFG in Chomsky Normal Form
     */
    std::shared_ptr<CFG> to_normal_form() {
        // Implementation will be added
        return nullptr;
    }
    
    /**
     * @brief Check if a word is in the language of the CFG
     * @param word The word to check
     * @return true if the word is in the language, false otherwise
     */
    bool contains(const std::vector<std::string>& word) {
        // Implementation will be added
        return false;
    }
    
    /**
     * @brief Get a string representation of the CFG
     * @return A string representation
     */
    std::string to_string() const {
        std::string result = "CFG:\n";
        
        result += "Variables: {";
        bool first = true;
        for (const auto& var : variables_) {
            if (!first) {
                result += ", ";
            }
            result += var->to_string();
            first = false;
        }
        result += "}\n";
        
        result += "Terminals: {";
        first = true;
        for (const auto& term : terminals_) {
            if (!first) {
                result += ", ";
            }
            result += term->to_string();
            first = false;
        }
        result += "}\n";
        
        if (start_symbol_) {
            result += "Start Symbol: " + start_symbol_->to_string() + "\n";
        } else {
            result += "Start Symbol: None\n";
        }
        
        result += "Productions:\n";
        for (const auto& prod : productions_) {
            result += "  " + prod->to_string() + "\n";
        }
        
        return result;
    }

private:
    /**
     * @brief Initialize a production in the CFG
     * @param production The production to initialize
     */
    void initialize_production_in_cfg(const ProductionPtr& production) {
        variables_.insert(production->head());
        
        for (const auto& cfg_object : production->body()) {
            if (auto terminal = std::dynamic_pointer_cast<Terminal>(cfg_object)) {
                terminals_.insert(terminal);
            } else if (auto variable = std::dynamic_pointer_cast<Variable>(cfg_object)) {
                variables_.insert(variable);
            }
        }
    }
    
    /**
     * @brief Get the generating or nullable symbols of the CFG
     * @param nullable Whether to get nullable symbols (true) or generating symbols (false)
     * @return The set of generating or nullable symbols
     */
    std::unordered_set<CFGObjectPtr> get_generating_or_nullable(bool nullable) {
        // Implementation will be added
        return {};
    }
    
    /**
     * @brief Set the impacts and remaining lists for the CFG
     */
    void set_impacts_and_remaining_lists() {
        // Implementation will be added
    }

private:
    VariableSet variables_;
    TerminalSet terminals_;
    VariablePtr start_symbol_;
    ProductionSet productions_;
    
    std::shared_ptr<CFG> normal_form_;
    std::optional<std::unordered_set<CFGObjectPtr>> generating_symbols_;
    std::optional<std::unordered_set<CFGObjectPtr>> nullable_symbols_;
    
    // For impacts and remaining lists
    std::unordered_map<CFGObjectPtr, std::vector<std::pair<VariablePtr, int>>> impacts_;
    std::unordered_map<VariablePtr, std::vector<int>> remaining_lists_;
    std::unordered_set<VariablePtr> added_impacts_;
};

} // namespace cfg
} // namespace cppformlang

#endif // CPPFORMLANG_CFG_H