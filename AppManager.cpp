#include "AppManager.h"

AppManager::AppManager() {
    videoManager = new VideoManager();
}

AppManager::~AppManager() {
    delete videoManager;
}

void AppManager::startApp() {
    cout << "Witaj w aplikacji!" << endl;
    showMenu();
}

void AppManager::showMenu() {
    string input;
    bool shalliBreak = false;

    cout << "\n--- MENU ---\n";
    videoManager->showExpireDate();
    cout << "0 - wyswietl liste wideo" << endl
    << "1 - wyswietl szczegolowe informacje o wideo" << endl
    << "2 - dodaj wideo" << endl
    << "3 - edytuj wideo" << endl
    << "4 - usun wideo" << endl
    << "5 - wyswietl liste ulubionych filmow" << endl
    << "6 - co by dzis obejrzec? " << endl
    << "7 - wyjdz" << endl;

    while(cin >> input) {
        if (input.length() > 1) {
            cout << "Nieprawidlowa wartosc.\n";
        } else if (input[0] == '0') {
            // show video list
            videoManager->showVideoList();
            break;
        } else if (input[0] == '1') {
            // show information about video
            videoManager->informationAboutVideo();
            break;
        } else if (input[0] == '2') {
            // add video
            videoManager->addVideo();
            videoManager->saveToFile();
            break;
        } else if (input[0] == '3') {
            // edit video
            videoManager->editVideo();
            videoManager->saveToFile();
            break;
        } else if (input[0] == '4') {
            // remove video
            videoManager->removeVideo();
            videoManager->saveToFile();
            break;
        } else if (input[0] == '5') {
            // show followed movies
            videoManager->showFollowed();
            break;
        } else if (input[0] == '6') {
            // recommend a video
            videoManager->recommend();
            break;
        } else if (input[0] == '7') {
            // exit
            shalliBreak = true;
            break;
        }
    }

    if(!shalliBreak) {
        cout << endl;
        system("pause");
        showMenu();
    }

}
