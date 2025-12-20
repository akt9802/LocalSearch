#include "crawler/FileCrawler.h"
#include "indexer/DocumentStore.h"
#include "indexer/InvertedIndex.h"
#include "indexer/PositionalInvertedIndex.h"
#include "search/TFIDFSearch.h"
#include "search/PhraseSearch.h"
#include "utils/TextUtils.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

void buildIndex(const std::string& docsPath) {
    std::unordered_set<std::string> stopwords = {
        "the", "is", "and", "a", "of"
    };

    auto files = FileCrawler::crawl(docsPath);

    DocumentStore store;
    InvertedIndex index;
    PositionalInvertedIndex posIndex;

    for (const auto& path : files) {
        std::ifstream in(path);
        if (!in) continue;

        std::string content((std::istreambuf_iterator<char>(in)),
                             std::istreambuf_iterator<char>());

        auto tokens = TextUtils::tokenize(content, stopwords);
        if (tokens.empty()) continue;

        int docId = store.addDocument(path, tokens.size());

        std::unordered_map<std::string, int> termCount;
        for (size_t i = 0; i < tokens.size(); i++) {
            index.addTerm(tokens[i], docId);
            termCount[tokens[i]]++;
            posIndex.addTerm(tokens[i], docId, i);
        }
        index.finalizeDocument(termCount);
    }

    store.save("data/index/docs.meta");
    index.save("data/index/inverted.idx");
    posIndex.save("data/index/positional.idx");

    std::cout << "Index built successfully\n";
}

void searchQuery(const std::string& query) {
    DocumentStore store;
    InvertedIndex index;

    store.load("data/index/docs.meta");
    index.load("data/index/inverted.idx");

    TFIDFSearch::search(query, index, store);
}

void phraseQuery(const std::string& phrase) {
    DocumentStore store;
    PositionalInvertedIndex posIndex;

    store.load("data/index/docs.meta");
    posIndex.load("data/index/positional.idx");

    PhraseSearch::search(phrase, posIndex, store);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage:\n"
                  << "./localsearch index <docs_path>\n"
                  << "./localsearch search <query>\n"
                  << "./localsearch phrase <phrase>\n";
        return 0;
    }

    std::string mode = argv[1];

    if (mode == "index") {
        buildIndex(argv[2]);
    }
    else if (mode == "search") {
        searchQuery(argv[2]);
    }
    else if (mode == "phrase") {
        phraseQuery(argv[2]);
    }
    else {
        std::cout << "Unknown command\n";
    }

    return 0;
}
