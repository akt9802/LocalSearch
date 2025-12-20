#include "PositionalInvertedIndex.h"
#include <fstream>
#include <sstream>

void PositionalInvertedIndex::addTerm(
    const std::string& term, int docId, int position) {
    index[term][docId].push_back(position);
}

bool PositionalInvertedIndex::hasTerm(const std::string& term) const {
    return index.find(term) != index.end();
}

const std::unordered_map<int, std::vector<int>>&
PositionalInvertedIndex::getPostings(const std::string& term) const {
    return index.at(term);
}

void PositionalInvertedIndex::save(const std::string& filePath) const {
    std::ofstream out(filePath);
    for (auto it = index.begin(); it != index.end(); ++it) {
        out << it->first << "|";
        for (auto p = it->second.begin(); p != it->second.end(); ++p) {
            out << p->first << ":";
            for (size_t i = 0; i < p->second.size(); i++) {
                out << p->second[i];
                if (i + 1 < p->second.size()) out << ",";
            }
            out << ";";
        }
        out << "\n";
    }
}

void PositionalInvertedIndex::load(const std::string& filePath) {
    index.clear();
    std::ifstream in(filePath);
    std::string line;

    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string term, rest;

        getline(ss, term, '|');
        getline(ss, rest);

        std::stringstream ds(rest);
        std::string docPart;

        while (getline(ds, docPart, ';')) {
            if (docPart.empty()) continue;

            size_t pos = docPart.find(':');
            int docId = stoi(docPart.substr(0, pos));
            std::string positions = docPart.substr(pos + 1);

            std::stringstream ps(positions);
            std::string num;
            while (getline(ps, num, ',')) {
                index[term][docId].push_back(stoi(num));
            }
        }
    }
}
