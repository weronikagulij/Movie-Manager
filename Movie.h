#ifndef MOVIE_H
#define MOVIE_H


#include <iostream>
#include "Video.h"

using namespace std;

class Movie: public Video {
    int rankingPosition;
public:
    void fillInformation();
    void showInformation();
    void getRemainingTime(bool &hasElementExpirationTime, double &difference);
    void informationFromText(string *data);
    void informationToText(string *data);
    string getType();
};

#endif
