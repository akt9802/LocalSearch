#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class PositionalInvertedIndex {
private:
    std::unordered_map<
        std::string,
        std::unordered_map<int, std::vector<int>>
    > index;

public:
    void addTerm(const std::string& term, int docId, int position);
    bool hasTerm(const std::string& term) const;

    const std::unordered_map<int, std::vector<int>>&
    getPostings(const std::string& term) const;

    void save(const std::string& filePath) const;
    void load(const std::string& filePath);

};
