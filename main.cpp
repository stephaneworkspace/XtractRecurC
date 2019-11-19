#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>  // for va_start
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

struct sFiles {
    string dir;
    string file_path;
    // const string CompleteDirFile() { return dir + file; }
};

static void format_msg(char *buf, size_t limit, char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buf, limit, format, args);
    va_end(args);
}

/* this can serve as the ls command implementation in c language */
#if 1
void listdir(const char *pathname, vector<sFiles> &vFiles)
{
    DIR *dp;
    struct dirent *dirp;
    char PATH[259] = {0};

    if ((dp = opendir(pathname)) == NULL) return;
    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_type == DT_DIR) {
            if ((strcmp(dirp->d_name, ".") == 0) ||
                (strcmp(dirp->d_name, "..") == 0))
                continue;
            sFiles files;
            files.dir = dirp->d_name;
            files.file_path = pathname;
            vFiles.push_back(files);
            // printf("%s%s\n", pathname, dirp->d_name);
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s/", dirp->d_name);
            files.dir = PATH;
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s%s/", pathname);

            files.file_path = PATH;
            vFiles.push_back(files);
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s%s/", pathname,
                       dirp->d_name);
            // snprintf(PATH, sizeof(PATH) - 1, "%s%s/", pathname,
            // dirp->d_name);
            listdir(PATH, vFiles);
        }
        else {
            sFiles files;
            files.dir = dirp->d_name;
            files.file_path = pathname;
            vFiles.push_back(files);
            // printf("%s%s\n", pathname, dirp->d_name);
        }
    }
    closedir(dp);
}
#endif

int main(int argc, char *argv[])
{
    // DIR *dp;
    // struct dirent *dirp;

    if (argc != 2) {
        printf("Please provide the directory to list out\n");
        exit(1);
    }

    // Define a vecotr
    vector<sFiles> vFiles;
    listdir(argv[1], vFiles);

    // Print all files
    for (auto &a : vFiles) {
        cout << a.dir << endl;
    }
    // Free mem
    vFiles.clear();
    exit(0);
}

