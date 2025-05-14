#ifndef CPPFORMLANG_PRODUCTION_H
#define CPPFORMLANG_PRODUCTION_H

#include "variable.h"
#include "terminal.h"
#include "epsilon.h"
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <algorithm>

namespace cppformlang {
namespace cfg {

/**
 * @brief Represents a production rule in a context-free grammar
 * 
 * This is the equivalent of pyformlang.cfg.production.Production
 */
class Production {
public:
    using CFGObjectPtr = std::shared_ptr<CFGObject>;
    using Body = std::vector<CFGObjectPtr>;
    
    /**
     * @brief Construct a new Production with the given head and body
     * @param head The variable on the left-hand side of the production
     * @param body The sequence of symbols on the right-hand side of the production
     * @param filtering Whether to filter out epsilon symbols from the body (default: true)
     */
    Production(std::shared_ptr<Variable> head, const Body& body, bool filtering = true)
        : head_(std::move(head)), body_(body) {
        if (filtering) {
            // Filter out epsilon symbols from the body
            body_.erase(
                std::remove_if(body_.begin(), body_.end(), 
                    [](const CFGObjectPtr& obj) {
                        return dynamic_cast<Epsilon*>(obj.get()) != nullptr;
                    }),
                body_.end()
            );
        }
    }
    
    /**
     * @brief Get the head (left-hand side) of the production
     * @return The head variable
     */
    const std::shared_ptr<Variable>& head() const {
        return head_;
    }
    
    /**
     * @brief Get the body (right-hand side) of the production
     * @return The body as a vector of CFGObjects
     */
    const Body& body() const {
        return body_;
    }
    
    /**
     * @brief Check if two Productions are equal
     * @param other The other Production to compare with
     * @return true if they are equal, false otherwise
     */
    bool operator==(const Production& other) const {
        if (*head_ != *other.head_ || body_.size() != other.body_.size()) {
            return false;
        }
        
        for (size_t i = 0; i < body_.size(); ++i) {
            if (*body_[i] != *other.body_[i]) {
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * @brief Check if two Productions are not equal
     * @param other The other Production to compare with
     * @return true if they are not equal, false otherwise
     */
    bool operator!=(const Production& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Get a string representation of the production
     * @return A string representation in the form "head -> body"
     */
    std::string to_string() const {
        std::string result = head_->to_string() + " -> ";
        
        if (body_.empty()) {
            result += "ε";
        } else {
            for (size_t i = 0; i < body_.size(); ++i) {
                if (i > 0) {
                    result += " ";
                }
                result += body_[i]->to_string();
            }
        }
        
        return result;
    }

private:
    std::shared_ptr<Variable> head_;
    Body body_;
};

} // namespace cfg
} // namespace cppformlang

// Hash function for Production to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::cfg::Production> {
        size_t operator()(const cppformlang::cfg::Production& prod) const {
            size_t result = hash<string>()(prod.head()->value());
            
            for (const auto& obj : prod.body()) {
                // Combine the hash with the hash of each object in the body
                result ^= hash<string>()(obj->value()) + 0x9e3779b9 + (result << 6) + (result >> 2);
            }
            
            return result;
        }
    };
}

#endif // CPPFORMLANG_PRODUCTION_H