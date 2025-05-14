#include <gtest/gtest.h>
#include <cppformlang/finite_automaton/deterministic_finite_automaton.h>
#include <memory>

using namespace cppformlang::finite_automaton;

TEST(DFATest, BasicConstruction) {
    // Create states
    auto q0 = std::make_shared<State>("q0");
    auto q1 = std::make_shared<State>("q1");
    
    // Create symbols
    auto a = std::make_shared<Symbol>("a");
    auto b = std::make_shared<Symbol>("b");
    
    // Create DFA
    auto dfa = std::make_shared<DeterministicFiniteAutomaton>();
    
    // Set start state
    dfa->set_start_state(q0);
    
    // Add final state
    dfa->add_final_state(q1);
    
    // Add transitions
    dfa->add_transition(q0, a, q1);
    dfa->add_transition(q0, b, q0);
    dfa->add_transition(q1, a, q1);
    dfa->add_transition(q1, b, q0);
    
    // Check that the DFA was constructed correctly
    EXPECT_EQ(dfa->states().size(), 2);
    EXPECT_EQ(dfa->input_symbols().size(), 2);
    EXPECT_EQ(dfa->start_state(), q0);
    EXPECT_EQ(dfa->final_states().size(), 1);
    
    // Check that the DFA accepts the correct words
    EXPECT_FALSE(dfa->accepts(std::vector<std::string>{}));
    EXPECT_TRUE(dfa->accepts(std::vector<std::string>{"a"}));
    EXPECT_FALSE(dfa->accepts(std::vector<std::string>{"b"}));
    EXPECT_TRUE(dfa->accepts(std::vector<std::string>{"a", "a"}));
    EXPECT_TRUE(dfa->accepts(std::vector<std::string>{"a", "b", "a"}));
}