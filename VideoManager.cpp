#include "VideoManager.h"
#include <fstream>
#include <algorithm>
#include "Series.h"
#include "Movie.h"
#include "LiveStream.h"
#include "validate.h"
#include <time.h>
#include "Utility.h"

int getGenreIndexByString(string s) {
    int i;

    for( int j = 0; j < Utility::filmGenresNumber(); j++ ) {
        if(Utility::filmGenres()[j] == s) {
            i = j;
            break;
        }
    }

    return i;
}

void showRemainingTime(double difference, string title) {
    int days, hours, minutes, seconds;

    days = difference / (60 * 60 * 24);
    hours = (difference - days *(60 * 60 * 24)) / (60 * 60);
    minutes = (difference - days *(60 * 60 * 24) - hours * (60 * 60)) / 60;
    seconds = difference - (days * 60 * 60 * 24 + hours * 60 * 60 + minutes * 60);

    cout << "\n---------\nDo live streamu " << title << " pozostalo: \n"
    << days << " dni, " << hours << " godzin, "
    << minutes << " minut, " << seconds << " sekund.\n\n";
}

// ---

VideoManager::VideoManager() {
    readFromFile();
}

VideoManager::~VideoManager() {
    for(int i = 0; i < videoList.size(); i++) {
        delete videoList[i];
    }
}

void VideoManager::saveToFile() {
    fstream file;
    string in;
    int maximum = max(Utility::fieldsMovie(), max(Utility::fieldsSeries(), Utility::fieldsLivestream()));
    int n = maximum;
    string data[maximum];
    file.open("videos.txt", ios::out);

    if(file.good()) {
	     for ( int i = 0; i < videoList.size(); i++ ) {
	        videoList[i]->informationToText(data);

	        file << videoList[i]->getType()<<endl;

	        if(videoList[i]->getType() == "Series") n = Utility::fieldsSeries();
	        else if(videoList[i]->getType() == "Movie") n = Utility::fieldsMovie();
	        else if(videoList[i]->getType() == "LiveStream") n = Utility::fieldsLivestream();

	        for(int j = 0; j < n; j ++ ) {
	            file << data[j]<<endl;
	        }

	        file << "-" << endl;
	    }
	} else throw string("Nie mozna otworzyc pliku videos.txt!");

    file.close();
}

void VideoManager::readFromFile() {
    fstream file;
    string in, data[9], type;

    file.open("videos.txt", ios::in);
    if ( file.good()) {
        while(!file.eof()) {
            getline(file, in); // line with type
            type = in;
            getline(file, in); // line with title
            data[0] = in;

            getline(file, in); // line with rating
            data[1] = in;

            getline(file, in); // information if is followed
            data[2] = in;

            getline(file, in); // line with genres
            data[3] = in;

            if(type == "Series") {
                getline(file, in); // line with number of episodes
                data[4] = in;
                videoList.push_back(new Series);
            } else if (type == "Movie") {
                getline(file, in);
                data[4] = in; // line with ranking position
                videoList.push_back(new Movie);
            } else if(type == "LiveStream") {
                getline(file, in); // year
                data[4] = in;
                getline(file, in); // month
                data[5] = in;
                getline(file, in); // day
                data[6] = in;
                getline(file, in); // hour
                data[7] = in;
                getline(file, in); // minute
                data[8] = in;
                videoList.push_back(new LiveStream);
            }

            videoList[videoList.size()-1]->informationFromText(data);

            getline(file, in);
            if(in != "-") throw string("W pliku videos.txt pojawil sie blad, filmy moga byc zle wyswietlne.");
        }
    } else {
       throw string("Nie znaleziono lub nie mozna otworzyc pliku videos.txt!");
    }
    file.close();
}

void VideoManager::recommend() {
    if(videoList.size() > 0) {
        int index = 0;

        cout << "Jak zarekomendowac film?\n"
        << "0 - najwyzsza ocena\n"
        << "1 - losowy traf\n"
        << "2 - wzgledem humoru\n";

        int nr = validate<int>(2);

        if (nr == 0) {
            int bestRate = videoList[0]->getRate();

            for(int i = 1; i < videoList.size(); i++ ) {
                if(videoList[i]->getRate() > bestRate) {
                    bestRate = videoList[i]->getRate();
                    index = i;
                }
            }
        } else if(nr == 1) {
            srand(time(NULL));
            index = rand() % videoList.size();
        } else if(nr == 2) {
            cout << "Jak sie teraz czujesz? \n"
            << "0 - smutno\n" << "1 - pelen energii\n" << "2 - szukam przemyslen\n" << "3 - zmeczony\n";

            int choice = validate<int>(3);
            // points of the film genre are kept in genres_points
            // it will be depending on user's choice
            float genres_points[Utility::filmGenresNumber()] = {0};
            switch (choice) {
            case 0:
                genres_points[7] += 1.0;
                genres_points[0] += 1.0;
                genres_points[6] += 0.25;
                break;
            case 1:
                genres_points[6] += 1.0;
                genres_points[1] += 1.0;
                genres_points[5] += 1.0;
                genres_points[3] += 0.25;
                break;
            case 2:
                genres_points[2] += 1.0;
                genres_points[8] += 0.25;
                genres_points[1] += 0.5;
                break;
            case 3:
                genres_points[0] += 0.5;
                genres_points[4] += 0.5;
                genres_points[7] += 1;
                genres_points[5] += 0.5;
                break;
            }

            // points of every movie is depending on its genres
            auto *video_points = new float [videoList.size()] ;
            for( int i = 0; i < videoList.size(); i++ ) {

                vector<string> g = videoList[i]->getGenres();
                for(int j = 0; j < g.size(); j ++ ) {
                    video_points[i] += 1.0*genres_points[getGenreIndexByString(g[j])];
                }
            }

            int bestScore = video_points[0];
            for( int i = 1; i < videoList.size(); i++ ) {
                if(video_points[i] > bestScore) {
                    bestScore = video_points[i];
                    index = i;
                }
            }
            delete video_points;
        }

        cout << "Najlepszy film na dzis to: " << index << " - " << videoList[index]->getTitle();
    } else {
        cout << "Nie ma jeszcze wideo ktore mozna polecic.\n";
    }
}

void VideoManager::showFollowed() {
    int followedCount = 0;
    cout << "--- ULUBIONE FILMY ---\n";
    if(videoList.size() == 0) cout << "Nie masz na razie zadnych video. \n";
    for (int i = 0; i < videoList.size(); i++ ) {
        if(videoList[i]->isElemFollowed() == true) {
            cout << i << " - " << videoList[i]->getTitle() << endl;
            followedCount ++;
        }
    }

    if (followedCount == 0) {
        cout << "Nie masz na razie zadnych ulubionych filmow.\n";
    }
}

void VideoManager::removeVideo() {
    if(videoList.size() > 0) {
        cout << "Ktore video usunac? \n";

        int n = validate<int>(videoList.size() - 1);
        delete videoList[n];
        videoList.erase(videoList.begin() + n);
        cout << "Video zostalo usuniete.\n";
    } else {
        cout << "Nie ma video ktore moznaby bylo usunac.\n";
    }
}

void VideoManager::editVideo() {
    if(videoList.size() > 0) {
        cout << "Ktore video chcesz edytowac? \n";

        int n = validate<int>(videoList.size() - 1);
        videoList[n]->fillInformation();
        cout << "Video zostalo zedytowane.\n";
    } else {
        cout << "Nie ma video ktore mozna byloby edytowac.\n";
    }
}

void VideoManager::showExpireDate() {
    double timeToExp;
    bool hasElementExpTime;
    string elemName;

    for(int i = 0; i < videoList.size(); i++) {
        videoList[i]->getRemainingTime(hasElementExpTime, timeToExp);
        if(hasElementExpTime == true) {
            // delete element timeToExp is less than 0
            if(timeToExp <=0) {
                delete videoList[i];
                videoList.erase(videoList.begin() + i);
            } else {
                showRemainingTime(timeToExp, videoList[i]->getTitle());
            }
        }
    }
}

void VideoManager::showVideoList() {
    cout << "\n--- LISTA WSZYSTKICH WIDEO --- \n";
    if(videoList.size() == 0) cout << "Nie masz na razie zadnych video. \n";
    for (int i = 0; i < videoList.size(); i++ ) {
        cout << i << " - " << videoList[i]->getTitle() << endl;
    }
}

void VideoManager::informationAboutVideo() {
    if(videoList.size() > 0) {
        cout << "O ktorym video wyswietlic informacje? \n";

        int n = validate<int>(videoList.size() - 1);
        videoList[n]->showInformation();
    } else {
        cout << "Nie ma video o ktorym mozna wyswietlic informacje.\n";
    }
}

void VideoManager::addVideo() {
    int nr;

    cout << "Jakiego typu wideo dodac?\nFilm - 0\nSerial - 1\nLive stream - 2\n";

    nr = validate<int>(2);

    if (nr == 0) {
        videoList.push_back(new Movie);
    } else if (nr == 1) {
        videoList.push_back(new Series);
    } else if (nr == 2) {
        videoList.push_back(new LiveStream);
    } else {

    }

    videoList[videoList.size()-1]->fillInformation();

    cout << "Wideo dodano pomyslnie.\n";
}


