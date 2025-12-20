#pragma once
#include "../indexer/InvertedIndex.h"
#include <string>

class KeywordSearch {
public:
    static void search(
        const std::string& term,
        const InvertedIndex& index
    );
};
