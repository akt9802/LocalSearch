#pragma once
#include "../indexer/PositionalInvertedIndex.h"
#include "../indexer/DocumentStore.h"
#include <string>

class PhraseSearch {
public:
    static void search(
        const std::string& phrase,
        const PositionalInvertedIndex& index,
        const DocumentStore& store
    );
};
