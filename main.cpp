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
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Please provide the directory to extract\n");
        exit(1);
    }
    string directory = argv[1];
    if (directory.back() != '/') {
        printf("Please provide a correct directory with end character \"/\"\n");
        exit(1);
    }
    Xtract xtract;
    xtract.run(argv[1]);
    exit(0);
}
