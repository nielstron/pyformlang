#ifndef CPPFORMLANG_CFG_OBJECT_H
#define CPPFORMLANG_CFG_OBJECT_H

#include <string>
#include <string_view>
#include <functional>

namespace cppformlang {
namespace cfg {

/**
 * @brief Base class for all CFG objects (variables and terminals)
 * 
 * This is the equivalent of pyformlang.cfg.cfg_object.CFGObject
 */
class CFGObject {
public:
    /**
     * @brief Construct a new CFGObject with the given value
     * @param value The string value of the object
     */
    explicit CFGObject(std::string value) : value_(std::move(value)) {}
    
    /**
     * @brief Virtual destructor for polymorphic behavior
     */
    virtual ~CFGObject() = default;
    
    /**
     * @brief Get the string value of the object
     * @return The string value
     */
    const std::string& value() const { return value_; }
    
    /**
     * @brief Check if two CFGObjects are equal
     * @param other The other CFGObject to compare with
     * @return true if they are equal, false otherwise
     */
    bool operator==(const CFGObject& other) const {
        return value_ == other.value_;
    }
    
    /**
     * @brief Check if two CFGObjects are not equal
     * @param other The other CFGObject to compare with
     * @return true if they are not equal, false otherwise
     */
    bool operator!=(const CFGObject& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Get a string representation of the object
     * @return A string representation
     */
    virtual std::string to_string() const {
        return value_;
    }
    
    /**
     * @brief Get the type of the CFGObject as a string
     * @return The type as a string
     */
    virtual std::string type() const = 0;

protected:
    std::string value_;
};

} // namespace cfg
} // namespace cppformlang

// Hash function for CFGObject to use in unordered containers
namespace std {
    template<>
    struct hash<cppformlang::cfg::CFGObject> {
        size_t operator()(const cppformlang::cfg::CFGObject& obj) const {
            return hash<string>()(obj.value());
        }
    };
}

#endif // CPPFORMLANG_CFG_OBJECT_H