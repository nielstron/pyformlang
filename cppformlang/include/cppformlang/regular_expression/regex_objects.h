#ifndef CPPFORMLANG_REGEX_OBJECTS_H
#define CPPFORMLANG_REGEX_OBJECTS_H

#include <string>
#include <memory>
#include <vector>

namespace cppformlang {
namespace regular_expression {

/**
 * @brief Base class for all regex objects
 */
class RegexObject {
public:
    /**
     * @brief Virtual destructor for polymorphic behavior
     */
    virtual ~RegexObject() = default;
    
    /**
     * @brief Get a string representation of the regex object
     * @return A string representation
     */
    virtual std::string to_string() const = 0;
};

/**
 * @brief Represents a symbol in a regular expression
 */
class Symbol : public RegexObject {
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
     * @brief Get a string representation of the symbol
     * @return A string representation
     */
    std::string to_string() const override {
        return value_;
    }

private:
    std::string value_;
};

/**
 * @brief Represents the empty string (epsilon) in a regular expression
 */
class Epsilon : public RegexObject {
public:
    /**
     * @brief Get a string representation of epsilon
     * @return The string "ε"
     */
    std::string to_string() const override {
        return "ε";
    }
};

/**
 * @brief Represents the empty language in a regular expression
 */
class EmptyLanguage : public RegexObject {
public:
    /**
     * @brief Get a string representation of the empty language
     * @return The string "∅"
     */
    std::string to_string() const override {
        return "∅";
    }
};

/**
 * @brief Represents the concatenation of two regex objects
 */
class Concatenation : public RegexObject {
public:
    /**
     * @brief Construct a new Concatenation of two regex objects
     * @param left The left regex object
     * @param right The right regex object
     */
    Concatenation(std::shared_ptr<RegexObject> left, std::shared_ptr<RegexObject> right)
        : left_(std::move(left)), right_(std::move(right)) {}
    
    /**
     * @brief Get the left regex object
     * @return The left regex object
     */
    const std::shared_ptr<RegexObject>& left() const { return left_; }
    
    /**
     * @brief Get the right regex object
     * @return The right regex object
     */
    const std::shared_ptr<RegexObject>& right() const { return right_; }
    
    /**
     * @brief Get a string representation of the concatenation
     * @return A string representation
     */
    std::string to_string() const override {
        return "(" + left_->to_string() + " · " + right_->to_string() + ")";
    }

private:
    std::shared_ptr<RegexObject> left_;
    std::shared_ptr<RegexObject> right_;
};

/**
 * @brief Represents the union (alternation) of two regex objects
 */
class Union : public RegexObject {
public:
    /**
     * @brief Construct a new Union of two regex objects
     * @param left The left regex object
     * @param right The right regex object
     */
    Union(std::shared_ptr<RegexObject> left, std::shared_ptr<RegexObject> right)
        : left_(std::move(left)), right_(std::move(right)) {}
    
    /**
     * @brief Get the left regex object
     * @return The left regex object
     */
    const std::shared_ptr<RegexObject>& left() const { return left_; }
    
    /**
     * @brief Get the right regex object
     * @return The right regex object
     */
    const std::shared_ptr<RegexObject>& right() const { return right_; }
    
    /**
     * @brief Get a string representation of the union
     * @return A string representation
     */
    std::string to_string() const override {
        return "(" + left_->to_string() + " + " + right_->to_string() + ")";
    }

private:
    std::shared_ptr<RegexObject> left_;
    std::shared_ptr<RegexObject> right_;
};

/**
 * @brief Represents the Kleene star of a regex object
 */
class KleeneStar : public RegexObject {
public:
    /**
     * @brief Construct a new KleeneStar of a regex object
     * @param obj The regex object
     */
    explicit KleeneStar(std::shared_ptr<RegexObject> obj) : obj_(std::move(obj)) {}
    
    /**
     * @brief Get the regex object
     * @return The regex object
     */
    const std::shared_ptr<RegexObject>& object() const { return obj_; }
    
    /**
     * @brief Get a string representation of the Kleene star
     * @return A string representation
     */
    std::string to_string() const override {
        return "(" + obj_->to_string() + ")*";
    }

private:
    std::shared_ptr<RegexObject> obj_;
};

} // namespace regular_expression
} // namespace cppformlang

#endif // CPPFORMLANG_REGEX_OBJECTS_H