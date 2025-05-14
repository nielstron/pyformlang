#include <cppformlang/cfg/cfg.h>
#include <algorithm>
#include <queue>

namespace cppformlang {
namespace cfg {

std::unordered_set<CFG::CFGObjectPtr> CFG::get_generating_or_nullable(bool nullable) {
    std::unordered_set<CFGObjectPtr> g_symbols;
    std::queue<CFGObjectPtr> to_process;
    
    // Add epsilon
    auto epsilon = std::make_shared<Epsilon>();
    g_symbols.insert(epsilon);
    to_process.push(epsilon);
    
    // Add terminals if not looking for nullable symbols
    if (!nullable) {
        for (const auto& terminal : terminals_) {
            g_symbols.insert(terminal);
            to_process.push(terminal);
        }
    }
    
    // Process symbols
    while (!to_process.empty()) {
        auto current = to_process.front();
        to_process.pop();
        
        // Find productions where current appears in the body
        for (const auto& production : productions_) {
            // Skip if the head is already in g_symbols
            if (g_symbols.find(production->head()) != g_symbols.end()) {
                continue;
            }
            
            // Check if all symbols in the body are in g_symbols
            bool all_in_g_symbols = true;
            for (const auto& symbol : production->body()) {
                if (g_symbols.find(symbol) == g_symbols.end()) {
                    all_in_g_symbols = false;
                    break;
                }
            }
            
            // If all symbols in the body are in g_symbols, add the head
            if (all_in_g_symbols) {
                g_symbols.insert(production->head());
                to_process.push(production->head());
            }
        }
    }
    
    // Remove epsilon
    g_symbols.erase(epsilon);
    
    return g_symbols;
}

} // namespace cfg
} // namespace cppformlang