#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <iostream>
#include "VideoManager.h"

using namespace std;

class AppManager {
    VideoManager *videoManager;
  public:
    AppManager();
    ~AppManager();
    void startApp();
    void showMenu();
};

#endif
