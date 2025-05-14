#include <gtest/gtest.h>
#include <cppformlang/regular_expression/regex.h>
#include <memory>

using namespace cppformlang::regular_expression;

TEST(RegexTest, BasicConstruction) {
    // Create regex objects
    auto a = std::make_shared<Symbol>("a");
    auto b = std::make_shared<Symbol>("b");
    
    // Create regex (a + b)*ab
    auto a_or_b = std::make_shared<Union>(a, b);
    auto star = std::make_shared<KleeneStar>(a_or_b);
    auto ab = std::make_shared<Concatenation>(a, b);
    auto regex_obj = std::make_shared<Concatenation>(star, ab);
    
    Regex regex(regex_obj);
    
    // Check that the regex was constructed correctly
    EXPECT_NE(regex.root(), nullptr);
    EXPECT_EQ(regex.to_string(), "((a + b)* · (a · b))");
}