#include "FileCrawler.h"
#include <dirent.h> // directory operations
#include <sys/stat.h>   // files/directory information (file is txt,json etc)
#include <cstring>  // string operations

using namespace std;

// dir is the current directory
// files is vector to store found file paths

void crawlHelper(const string& dir, vector<string>& files) {
    // lets use c_str which converts C++ strings to c-style char array
    // here DIR is a C structure that represents an open directory(defined in <dirent.h>)
    // DIR* is pointer to that structure
    DIR* dp = opendir(dir.c_str());
    if (!dp) return;

    // dirent = directory entry, it seperate one file/folder in the directory
    // contains information about that entry
    struct dirent* entry;
    while ((entry = readdir(dp)) != nullptr) {
        // readdir(dp) - it will read next entry in the directory
        // entry->d_name will access the name field
        string name = entry->d_name;

        // data/docs/
        // ├── .          ← Current directory (skip!)
        // ├── ..         ← Parent directory = data/ (skip!)
        // ├── a.txt
        // ├── report.pdf
        // └── sub/
        if (name == "." || name == "..") continue;

        string path = dir + "/" + name;

        // a C structure that stores files/directory metadata
        struct stat info;

        // getting file metadata
        // path.c_str() == file path a C-styled string
        // pointer to info struct we declared
        // if stat() failed(retured non zero), skip to next iteration
        // 0 on success 
        if (stat(path.c_str(), &info) != 0) continue;

        // st_mode is inside info, st_mode->file type and permission
        // check if directory or not
        if (S_ISDIR(info.st_mode)) {
            // recursive call for this directory
            crawlHelper(path, files);
        }

        // else if it is regular file (a.txt)
        else if (S_ISREG(info.st_mode)) {
            // path.size() > 4 (a.txt)
            if (path.size() >= 4 &&
                path.substr(path.size() - 4) == ".txt") {
                files.push_back(path);
            }
        }
    }
    // close the directory
    closedir(dp);
}

vector<string> FileCrawler::crawl(const string& rootDir) {
    vector<string> files;
    crawlHelper(rootDir, files);
    return files;
}
