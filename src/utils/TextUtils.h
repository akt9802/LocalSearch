#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class TextUtils {
public:
    static std::string toLower(const std::string& s);

    static std::vector<std::string> tokenize(
        const std::string& text,
        const std::unordered_set<std::string>& stopwords
    );
};
