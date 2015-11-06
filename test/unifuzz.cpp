// Copyright 2015 W.J. van der Laan
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//
// Parses and formats data passed on stdin. Does not produce any output. Exit
// status will be 0 on valid JSON, 1 if there was a parse error.
// Meant to be used with a fuzzer, for example afl:
//
//   afl-fuzz -i pass_in -o out -- test/unifuzz

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <string>
#include "univalue.h"

int main (int argc, char *argv[])
{
    std::string jdata;

    char buf[4096];
    while (!feof(stdin)) {
            int bread = fread(buf, 1, sizeof(buf), stdin);
            assert(!ferror(stdin));
            jdata.append(buf, buf+bread);
    }

    UniValue val;
    if (val.read(jdata)) {
        std::string s = val.write();
        return 0;
    }
    return 1;
}

