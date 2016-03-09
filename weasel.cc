// Evolver - "Dawkins Weasel" genetic algorithm (main program)
//
// By Jaldhar H. Vyas <jaldhar@braincells.com>
//
// (C) 2016 Consolidated Braincells Inc.  All rights reserved.
// "Do What Thou Wilt" Shall Be The Whole Of The License.

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
using namespace std;

#include "evolver.h"

void usage(const char* progname) {
    cerr <<
        "Usage: " << progname << " [-c copies][-t threshold] string" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int numCopies = 100;
    int mutationThreshold = 5;

    int opt;
    try {
        while ((opt = getopt(argc, argv, "h?c:t:")) != -1) {
            switch (opt) {
            case 'c':
                numCopies = stoi(optarg);
                if (numCopies < 1) {
                    throw out_of_range("argument to -c must be > 0");
                }
                break;
            case 't':
                mutationThreshold = stoi(optarg);
                if (mutationThreshold < 1 || mutationThreshold > 99) {
                    throw out_of_range("argument to -t must be from 1 to 99");
                }
                break;
            case 'h':
            case '?':
            default:
                usage(argv[0]);
            }
        }
    }
    catch(exception& e) {
        cerr << argv[0] << ": " << e.what() << endl;
        usage(argv[0]);
    }

    const char* targetPhrase = (optind >= argc)
        ? "METHINKS IT IS LIKE A WEASEL" : argv[optind];

    Evolver weasel(targetPhrase, numCopies, mutationThreshold);
    int generation = 0;

    for (auto w: weasel) {
        cout << right << setfill('0') << setw(4) << generation << ' ' <<
            w._phrase << " (" <<  w._score << ')' << endl;
        generation++;
    }

    return EXIT_SUCCESS;
}
