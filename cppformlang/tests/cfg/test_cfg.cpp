#include <gtest/gtest.h>
#include <cppformlang/cfg/cfg.h>
#include <memory>

using namespace cppformlang::cfg;

TEST(CFGTest, BasicConstruction) {
    // Create variables
    auto S = std::make_shared<Variable>("S");
    auto A = std::make_shared<Variable>("A");
    
    // Create terminals
    auto a = std::make_shared<Terminal>("a");
    auto b = std::make_shared<Terminal>("b");
    
    // Create productions
    auto p1 = std::make_shared<Production>(S, std::vector<std::shared_ptr<CFGObject>>{A, a});
    auto p2 = std::make_shared<Production>(A, std::vector<std::shared_ptr<CFGObject>>{b});
    
    // Create CFG
    CFG grammar({S, A}, {a, b}, S, {p1, p2});
    
    // Check that the CFG was constructed correctly
    EXPECT_EQ(grammar.variables().size(), 2);
    EXPECT_EQ(grammar.terminals().size(), 2);
    EXPECT_EQ(grammar.start_symbol(), S);
    EXPECT_EQ(grammar.productions().size(), 2);
}