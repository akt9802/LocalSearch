#include "KeywordSearch.h"
#include <iostream>

void KeywordSearch::search(
    const std::string& term,
    const InvertedIndex& index
) {
    if (!index.hasTerm(term)) {
        std::cout << "No results found for: " << term << "\n";
        return;
    }

    const auto& postings = index.getPostingList(term);

    std::cout << "Results for \"" << term << "\":\n";
    for (auto it = postings.begin(); it != postings.end(); ++it) {
        std::cout << "DocID: " << it->first
                  << " | Frequency: " << it->second << "\n";
    }
}
