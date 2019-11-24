/******************************************************************************
 * XtractRecurC
 * By Stéphane Bressani
 *  ____  _             _
 * / ___|| |_ ___ _ __ | |__   __ _ _ __   ___
 * \___ \| __/ _ \ '_ \| '_ \ / _` | '_ \ / _ \
 *  ___) | ||  __/ |_) | | | | (_| | | | |  __/
 * |____/ \__\___| .__/|_| |_|\__,_|_| |_|\___|
 *               | |stephane-bressani.ch
 *               |_|github.com/stephaneworkspace
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#include "xtract.h"
// Include for ls
#include <dirent.h>
#include <errno.h>
// fstat
//#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
#include <iostream>
// Include for vecotor sort
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
// Include for uid
#include <pwd.h>
using namespace std;

Xtract::Xtract() {}

void Xtract::run(char *extract_path)
{
    // Define a vector
    vector<sFiles> vFiles;
    listdir(extract_path, vFiles);

    // Extract all files
    string command;
    for (auto &a : vFiles) {
        switch (a.TypeExt()) {
            case Xtract::Compress::TAR_GZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "tar xvf " + a.CompletePathFile() + " -C " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case Xtract::Compress::GZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "gunzip " + a.CompletePathFile() + " > " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case Xtract::Compress::TGZ:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "tar zxvf " + a.CompletePathFile() + " -C " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case Xtract::Compress::ZIP:
                command = "mkdir " + a.ExtractionNewPath();
                system(command.c_str());
                command = "unzip " + a.CompletePathFile() + " -d " +
                          a.ExtractionNewPath();
                system(command.c_str());
                command = "rm " + a.CompletePathFile();
                system(command.c_str());
                break;
            case Xtract::Compress::UNKNOWN:
                break;
        }
    }

    // Free mem
    vFiles.clear();
}
void Xtract::format_msg(char *buf, size_t limit, char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buf, limit, format, args);
    va_end(args);
}
void Xtract::listdir(const char *pathname, vector<sFiles> &vFiles)
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
            // printf("%s%s\n", pathname, dirp->d_name);
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
