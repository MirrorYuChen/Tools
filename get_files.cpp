#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif
#include <algorithm>
#include <string>
#include <vector>
#include <string.h>


int main(int argc, char* argv[]) {
    std::string image_path = "./images";
    std::vector<std::string> files;
#if defined(_MSC_VER)
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    hFind = FindFirstFile(image_path.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind) {
        printf("Error to open %s\n", image_path.c_str());
        return -1;
    }
    do {
        if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(ffd.cFileName) && GetLastError() != ERROR_FILE_NOT_FOUND) {
            files.push_back(ffd.cFileName);
        }
    } while(FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
#else
    struct stat s;
    lstat(image_path.c_str(), &s);
    struct dirent* file_name;
    DIR* dir;
    dir = opendir(image_path.c_str());
    while((file_name = readdir(dir)) != nullptr) {
        if (strcmp(file_name->d_name, ".") == 0 || strcmp(file_name->d_name, "..") == 0) {
            continue;
        }
        files.push_back(file_name->d_name);
    }
#endif
    std::sort(files.begin(), files.end());
    for (int i = 0; i < files.size(); ++i) {
        printf("file name: %s.\n", files[i].c_str());
    }
    return 0;
}