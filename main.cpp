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

enum eCompress { TAR_GZ = 0, GZ = 1, TGZ = 2, ZIP = 3, UNKNOWN = -1 };

struct sFiles {
    string file_name;
    string file_path;
    const string CompletePathFile() { return file_path + file_name; }
    const string ExtractionNewPath()
    {
        char *c_file_name = strdup(file_name.c_str());
        char *token;

        token = strtok(c_file_name, ".");
        return file_path + token;
    }
    const string ExtractionExt()
    {
        char *c_file_name = strdup(file_name.c_str());
        const char s[2] = ".";
        char *token;
        string ext = "";
        token = strtok(c_file_name, s);
        int i = 0;
        while (token != NULL) {
            if (i > 0) {
                ext += string(".") + string(token);
            }
            i++;
            token = strtok(NULL, s);
        }
        return ext;
    }
    int TypeExt()
    {
        const string EXT = ExtractionExt();
        if (EXT == ".tar.gz")
            return eCompress::TAR_GZ;
        else if (EXT == ".gz")
            return eCompress::GZ;
        else if (EXT == ".tgz")
            return eCompress::TGZ;
        else if (EXT == ".zip")
            return eCompress::ZIP;
        else
            return eCompress::UNKNOWN;
    }
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
            /*sFiles files;
            files.dir = dirp->d_name;
            files.file_path = pathname;
            vFiles.push_back(files);
            */

            // printf("%s%s\n", pathname, dirp->d_name);

            /*
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s/", dirp->d_name);
            files.dir = PATH;
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s%s/", pathname);

            files.file_path = PATH;
            vFiles.push_back(files);
            */
            format_msg(PATH, sizeof(PATH) - 1, (char *)"%s%s/", pathname,
                       dirp->d_name);
            // snprintf(PATH, sizeof(PATH) - 1, "%s%s/", pathname,
            // dirp->d_name);
            listdir(PATH, vFiles);
        }
        else {
            sFiles files;
            files.file_name = dirp->d_name;
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

    // Extract all files
    string command;
    for (auto &a : vFiles) {
        switch (a.TypeExt()) {
            case eCompress::TAR_GZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "tar xvf " + a.CompletePathFile() + " -C " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case eCompress::GZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "gunzip " + a.CompletePathFile() + " > " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case eCompress::TGZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "tar zxvf " + a.CompletePathFile() + " -C " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case eCompress::ZIP:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "unzip " + a.CompletePathFile() + " -d " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
        }
    }
    // Free mem
    vFiles.clear();
    exit(0);
}
