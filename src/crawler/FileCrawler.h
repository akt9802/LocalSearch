#pragma once
#include <vector>
#include <string>

class FileCrawler {
public:
    static std::vector<std::string> crawl(const std::string& rootDir);
};
