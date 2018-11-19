#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

using namespace std;

class Utility {

public:
    static int fieldsLivestream() {
        return 9;
    }

    static int fieldsSeries() {
        return 5;
    }

    static int fieldsMovie() {
        return 5;
    }

    static int filmGenresNumber() {
        return 9;
    }

    static vector<string> filmGenres() {
        vector<string> filmGenres;
        filmGenres.push_back("comedy");
        filmGenres.push_back("sci-fi");
        filmGenres.push_back("history");
        filmGenres.push_back("action");
        filmGenres.push_back("adventure");
        filmGenres.push_back("drama");
        filmGenres.push_back("western");
        filmGenres.push_back("horror");
        filmGenres.push_back("thriller");
        return filmGenres;
    }

};

#endif
