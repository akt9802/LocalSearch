
// this is header file for the crawler 
// interface/declaration file ( it tells compiler what FileCrawler file look like)

#pragma once    // prevent file from being included multiple times in the same compilation
#include <vector>
#include <string>

using namespace std;
class FileCrawler {
public:
    static vector<string> crawl(const string& rootDir);
};
