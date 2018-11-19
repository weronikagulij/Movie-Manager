#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <vector>

using namespace std;
			      
class Video {
    string title;
    float ratingOnIMDb;
    bool isFollowed;
    vector <string> genres;

public:
    virtual void fillInformation();
    virtual void showInformation();
    virtual void getRemainingTime(bool &hasElementExpirationTime, double &difference)=0;
    void follow();
    string getTitle();
    bool isElemFollowed();
    float getRate();
    vector <string> getGenres();
    virtual void informationFromText(string *data);
    virtual void informationToText(string *data);
    virtual string getType()=0;
};
#endif
