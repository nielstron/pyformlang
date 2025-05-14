#include <cppformlang/cfg/cfg.h>
#include <cppformlang/finite_automaton/deterministic_finite_automaton.h>
#include <cppformlang/regular_expression/regex.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace cppformlang;

void cfg_example() {
    std::cout << "=== Context-Free Grammar Example ===" << std::endl;
    
    // Create variables
    auto S = std::make_shared<cfg::Variable>("S");
    auto A = std::make_shared<cfg::Variable>("A");
    auto B = std::make_shared<cfg::Variable>("B");
    
    // Create terminals
    auto a = std::make_shared<cfg::Terminal>("a");
    auto b = std::make_shared<cfg::Terminal>("b");
    
    // Create productions
    auto p1 = std::make_shared<cfg::Production>(S, std::vector<std::shared_ptr<cfg::CFGObject>>{A, B});
    auto p2 = std::make_shared<cfg::Production>(A, std::vector<std::shared_ptr<cfg::CFGObject>>{a, A});
    auto p3 = std::make_shared<cfg::Production>(A, std::vector<std::shared_ptr<cfg::CFGObject>>{a});
    auto p4 = std::make_shared<cfg::Production>(B, std::vector<std::shared_ptr<cfg::CFGObject>>{b, B});
    auto p5 = std::make_shared<cfg::Production>(B, std::vector<std::shared_ptr<cfg::CFGObject>>{b});
    
    // Create CFG
    cfg::CFG grammar(
        {S, A, B},
        {a, b},
        S,
        {p1, p2, p3, p4, p5}
    );
    
    std::cout << grammar.to_string() << std::endl;
    
    // TODO: Add more examples when implementation is complete
}

void dfa_example() {
    std::cout << "=== Deterministic Finite Automaton Example ===" << std::endl;
    
    // Create states
    auto q0 = std::make_shared<finite_automaton::State>("q0");
    auto q1 = std::make_shared<finite_automaton::State>("q1");
    auto q2 = std::make_shared<finite_automaton::State>("q2");
    
    // Create symbols
    auto a = std::make_shared<finite_automaton::Symbol>("a");
    auto b = std::make_shared<finite_automaton::Symbol>("b");
    
    // Create DFA
    auto dfa = std::make_shared<finite_automaton::DeterministicFiniteAutomaton>();
    
    // Set start state
    dfa->set_start_state(q0);
    
    // Add final state
    dfa->add_final_state(q2);
    
    // Add transitions
    dfa->add_transition(q0, a, q1);
    dfa->add_transition(q0, b, q0);
    dfa->add_transition(q1, a, q1);
    dfa->add_transition(q1, b, q2);
    dfa->add_transition(q2, a, q1);
    dfa->add_transition(q2, b, q0);
    
    std::cout << dfa->to_string() << std::endl;
    
    // Check if the DFA accepts some words
    std::vector<std::vector<std::string>> words = {
        {},
        {"a"},
        {"b"},
        {"a", "b"},
        {"b", "a", "b"},
        {"a", "a", "b"}
    };
    
    for (const auto& word : words) {
        std::string word_str;
        for (const auto& symbol : word) {
            word_str += symbol;
        }
        std::cout << "Word \"" << word_str << "\" is " 
                  << (dfa->accepts(word) ? "accepted" : "rejected") << std::endl;
    }
}

void regex_example() {
    std::cout << "=== Regular Expression Example ===" << std::endl;
    
    // Create regex objects
    auto a = std::make_shared<regular_expression::Symbol>("a");
    auto b = std::make_shared<regular_expression::Symbol>("b");
    
    // Create regex (a + b)*ab
    auto a_or_b = std::make_shared<regular_expression::Union>(a, b);
    auto star = std::make_shared<regular_expression::KleeneStar>(a_or_b);
    auto ab = std::make_shared<regular_expression::Concatenation>(a, b);
    auto regex_obj = std::make_shared<regular_expression::Concatenation>(star, ab);
    
    regular_expression::Regex regex(regex_obj);
    
    std::cout << "Regex: " << regex.to_string() << std::endl;
    
    // TODO: Add more examples when implementation is complete
}

int main() {
    cfg_example();
    std::cout << std::endl;
    
    dfa_example();
    std::cout << std::endl;
    
    regex_example();
    
    return 0;
}