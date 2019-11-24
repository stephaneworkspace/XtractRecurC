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
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class Xtract {
public:
    Xtract();
    enum class Compress { TAR_GZ, GZ, TGZ, ZIP, UNKNOWN };
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
        Compress TypeExt()
        {
            const string EXT = ExtractionExt();
            if (EXT == ".tar.gz")
                return Compress::TAR_GZ;
            else if (EXT == ".gz")
                return Compress::GZ;
            else if (EXT == ".tgz")
                return Compress::TGZ;
            else if (EXT == ".zip")
                return Compress::ZIP;
            else {
                printf("Ignored: %s\n", EXT.c_str());
                return Compress::UNKNOWN;
            }
        }
    };

    struct sLs {
        string name;
        int id;
        int mode;
        bool operator<(const sLs &a) const { return name < a.name; }
    };
    void run(char *extract_path);

private:
    static void format_msg(char *buf, size_t limit, char *format, ...);
    void listdir(const char *pathname, vector<sFiles> &vFiles);
};
