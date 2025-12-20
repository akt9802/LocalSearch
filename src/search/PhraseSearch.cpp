#include "PhraseSearch.h"
#include "../utils/TextUtils.h"
#include <iostream>
#include <unordered_set>

void PhraseSearch::search(
    const std::string& phrase,
    const PositionalInvertedIndex& index,
    const DocumentStore& store
) {
    std::unordered_set<std::string> noStopwords;
    auto tokens = TextUtils::tokenize(phrase, noStopwords);

    if (tokens.size() < 2) {
        std::cout << "Phrase search requires at least 2 words\n";
        return;
    }

    // First term postings
    if (!index.hasTerm(tokens[0])) {
        std::cout << "No results\n";
        return;
    }

    const auto& firstPostings = index.getPostings(tokens[0]);

    std::cout << "\n--- PHRASE SEARCH RESULTS ---\n";

    for (auto it = firstPostings.begin(); it != firstPostings.end(); ++it) {
        int docId = it->first;
        const std::vector<int>& positions = it->second;

        bool match = true;

        for (size_t t = 1; t < tokens.size(); t++) {
            if (!index.hasTerm(tokens[t])) {
                match = false;
                break;
            }

            const auto& postings = index.getPostings(tokens[t]);
            if (postings.find(docId) == postings.end()) {
                match = false;
                break;
            }

            const std::vector<int>& nextPositions =
                postings.at(docId);

            bool found = false;
            for (size_t i = 0; i < positions.size(); i++) {
                for (size_t j = 0; j < nextPositions.size(); j++) {
                    if (nextPositions[j] == positions[i] + (int)t) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }

            if (!found) {
                match = false;
                break;
            }
        }

        if (match) {
            std::cout << "DocID: " << docId
                      << " | Path: "
                      << store.getDocument(docId).path
                      << "\n";
        }
    }
}
