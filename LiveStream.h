#ifndef LIVESTREAM_H
#define LIVESTREAM_H

#include <iostream>
#include "Video.h"

using namespace std;

class LiveStream: public Video {
    struct tm *startDate;
    struct timeInDays *remainingTime;
public:
    ~LiveStream();
    void fillInformation();
    void showInformation();
    void getRemainingTime(bool &hasElementExpirationTime, double &difference);
    void informationFromText(string *data);
    void informationToText(string *data);
    string getType();
};

#endif
