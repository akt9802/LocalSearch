#include "FileCrawler.h"
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

void crawlHelper(const std::string& dir,
                 std::vector<std::string>& files) {

    DIR* dp = opendir(dir.c_str());
    if (!dp) return;

    struct dirent* entry;
    while ((entry = readdir(dp)) != nullptr) {

        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string path = dir + "/" + name;

        struct stat info;
        if (stat(path.c_str(), &info) != 0) continue;

        if (S_ISDIR(info.st_mode)) {
            crawlHelper(path, files);
        }
        else if (S_ISREG(info.st_mode)) {
            if (path.size() >= 4 &&
                path.substr(path.size() - 4) == ".txt") {
                files.push_back(path);
            }
        }
    }
    closedir(dp);
}

std::vector<std::string> FileCrawler::crawl(const std::string& rootDir) {
    std::vector<std::string> files;
    crawlHelper(rootDir, files);
    return files;
}
