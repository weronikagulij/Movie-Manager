#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <iostream>
#include <vector>
#include "Video.h"

using namespace std;

class VideoManager {
    vector <Video*> videoList;
    void readFromFile();
public:
    VideoManager();
    ~VideoManager();
    void saveToFile();
    void addVideo();
    void showVideoList();
    void informationAboutVideo();
    void showExpireDate();
    void editVideo();
    void removeVideo();
    void showFollowed();
    void recommend();
};

#endif
