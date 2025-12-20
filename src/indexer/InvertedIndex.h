#pragma once
#include <unordered_map>
#include <string>

class InvertedIndex {
private:
    std::unordered_map<std::string,
        std::unordered_map<int, int>> index;

    std::unordered_map<std::string, int> docFreq;

public:
    void addTerm(const std::string& term, int docId);
    void finalizeDocument(const std::unordered_map<std::string, int>& termCount);

    bool hasTerm(const std::string& term) const;
    const std::unordered_map<int, int>& getPostingList(const std::string& term) const;

    void save(const std::string& filePath) const;
    void load(const std::string& filePath);

};
