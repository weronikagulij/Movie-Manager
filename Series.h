#ifndef SERIES_H
#define SERIES_H
#include <iostream>
#include "Video.h"

using namespace std;

class Series: public Video {
    int howManyEpisodes;
public:
    void getRemainingTime(bool &hasElementExpirationTime, double &difference);
    void fillInformation();
    void showInformation();
    void informationFromText(string *data);
    void informationToText(string *data);
    string getType();
};

#endif
