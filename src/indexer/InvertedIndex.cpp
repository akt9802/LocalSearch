#include "InvertedIndex.h"
#include <fstream>
#include <sstream>

void InvertedIndex::addTerm(const std::string& term, int docId) {
    index[term][docId]++;
}

void InvertedIndex::finalizeDocument(
    const std::unordered_map<std::string, int>& termCount) {
    for (auto it = termCount.begin(); it != termCount.end(); ++it) {
        docFreq[it->first]++;
    }
}

bool InvertedIndex::hasTerm(const std::string& term) const {
    return index.find(term) != index.end();
}

const std::unordered_map<int, int>&
InvertedIndex::getPostingList(const std::string& term) const {
    return index.at(term);
}

void InvertedIndex::save(const std::string& filePath) const {
    std::ofstream out(filePath);
    for (auto it = index.begin(); it != index.end(); ++it) {
        out << it->first << "|";
        for (auto p = it->second.begin(); p != it->second.end(); ++p) {
            out << p->first << ":" << p->second << ",";
        }
        out << "\n";
    }
}

void InvertedIndex::load(const std::string& filePath) {
    index.clear();
    docFreq.clear();

    std::ifstream in(filePath);
    std::string line;

    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string term, postings;

        getline(ss, term, '|');
        getline(ss, postings);

        std::stringstream ps(postings);
        std::string pair;
        int df = 0;

        while (getline(ps, pair, ',')) {
            if (pair.empty()) continue;
            size_t pos = pair.find(':');
            int docId = stoi(pair.substr(0, pos));
            int freq = stoi(pair.substr(pos + 1));
            index[term][docId] = freq;
            df++;
        }
        docFreq[term] = df;
    }
}
