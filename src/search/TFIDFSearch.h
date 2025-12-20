#pragma once
#include "../indexer/InvertedIndex.h"
#include "../indexer/DocumentStore.h"
#include <string>

class TFIDFSearch {
public:
    static void search(
        const std::string& query,
        const InvertedIndex& index,
        const DocumentStore& store
    );
};
