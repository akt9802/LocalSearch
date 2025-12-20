#include "TFIDFSearch.h"
#include "../utils/TextUtils.h"
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

void TFIDFSearch::search(
    const std::string& query,
    const InvertedIndex& index,
    const DocumentStore& store
) {
    std::unordered_set<std::string> noStopwords;
    auto queryTokens = TextUtils::tokenize(query, noStopwords);

    std::unordered_map<int, double> scores;
    int totalDocs = store.size();

    for (size_t i = 0; i < queryTokens.size(); i++) {
        const std::string& term = queryTokens[i];

        if (!index.hasTerm(term))
            continue;

        const auto& postings = index.getPostingList(term);
        int df = postings.size();
        double idf = std::log((double)totalDocs / df);

        for (auto it = postings.begin(); it != postings.end(); ++it) {
            int docId = it->first;
            int tfCount = it->second;

            int docLen = store.getDocument(docId).length;
            double tf = (double)tfCount / docLen;

            scores[docId] += tf * idf;
        }
    }

    // Convert to vector for sorting
    std::vector<std::pair<int, double>> results;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        results.push_back(*it);
    }

    std::sort(results.begin(), results.end(),
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            return a.second > b.second;
        });

    std::cout << "\n--- TF-IDF RESULTS ---\n";
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "DocID: " << results[i].first
                  << " | Score: " << results[i].second << "\n";
    }
}
