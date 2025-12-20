#pragma once
#include <string>

struct Document {
    int docId;
    std::string path;
    int length;   // number of tokens
};
