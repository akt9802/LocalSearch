#include "TextUtils.h"
#include <cctype>

std::string TextUtils::toLower(const std::string& s) {
    std::string result;
    for (char c : s) {
        result += std::tolower(c);
    }
    return result;
}

std::vector<std::string> TextUtils::tokenize(
    const std::string& text,
    const std::unordered_set<std::string>& stopwords
) {
    std::vector<std::string> tokens;
    std::string word;

    for (char c : text) {
        if (std::isalpha(c)) {
            word += std::tolower(c);
        } else {
            if (!word.empty() && !stopwords.count(word)) {
                tokens.push_back(word);
            }
            word.clear();
        }
    }

    // handle last word
    if (!word.empty() && !stopwords.count(word)) {
        tokens.push_back(word);
    }

    return tokens;
}
