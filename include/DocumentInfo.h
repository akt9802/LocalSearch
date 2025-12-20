#ifndef DOCUMENT_INFO_H
#define DOCUMENT_INFO_H

#include <string>

struct DocumentInfo {
    int docID;
    std::string path;

    // NOTE:
    // Later we will add:
    // int length;
    // double score;
};

#endif
