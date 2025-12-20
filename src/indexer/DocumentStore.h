#pragma once
#include <string>
#include <vector>

struct Document {
    int docId;
    std::string path;
    int length;
};

class DocumentStore {
private:
    std::vector<Document> documents;

public:
    int addDocument(const std::string& path, int length);
    const Document& getDocument(int docId) const;
    int size() const;

    void save(const std::string& filePath) const;
    void load(const std::string& filePath);
};
