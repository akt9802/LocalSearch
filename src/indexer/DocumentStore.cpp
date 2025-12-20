#include "DocumentStore.h"
#include <fstream>
#include <sstream>

int DocumentStore::addDocument(const std::string& path, int length) {
    int docId = documents.size();
    documents.push_back({docId, path, length});
    return docId;
}

const Document& DocumentStore::getDocument(int docId) const {
    return documents.at(docId);
}

int DocumentStore::size() const {
    return documents.size();
}

void DocumentStore::save(const std::string& filePath) const {
    std::ofstream out(filePath);
    for (size_t i = 0; i < documents.size(); i++) {
        out << documents[i].docId << "|"
            << documents[i].path << "|"
            << documents[i].length << "\n";
    }
}

void DocumentStore::load(const std::string& filePath) {
    documents.clear();
    std::ifstream in(filePath);
    std::string line;

    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string part;

        Document doc;
        getline(ss, part, '|'); doc.docId = stoi(part);
        getline(ss, part, '|'); doc.path = part;
        getline(ss, part, '|'); doc.length = stoi(part);

        documents.push_back(doc);
    }
}