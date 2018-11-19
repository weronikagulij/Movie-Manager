#include "Video.h"
#include "validate.h"
#include <algorithm>
#include "Utility.h"

void Video::informationToText(string *data) {
    data[0] = title;
    data[1] = to_string(ratingOnIMDb);

    if(isFollowed == true) data[2] = "true";
    else data[2] = "false";

    data[3] = "";
    for( int i = 0; i < genres.size(); i++ ) {
        data[3] += genres[i];
        if(i < genres.size() - 1) data[3] += " ";
    }
}

void Video::informationFromText(string *data) {
    title = data[0];
    ratingOnIMDb = stof(data[1]);
    if(data[2] == "true" ) isFollowed = true;
    else isFollowed = false;

    string genre = "";
    for(int i = 0; i < data[3].length(); i++ ) {
        if(data[3][i] == ' ') {
            genres.push_back(genre);
            genre = "";
        } else genre += data[3][i];
    }
    if ( data[3].length() > 0 ) genres.push_back(genre);
}

vector<string> Video::getGenres() {
    return genres;
}

float Video::getRate() {
    return ratingOnIMDb;
}

string Video::getTitle() {
    return title;
}

void Video::fillInformation() {
    string title, nr;
    int nrToInt;
    float ratingOnIMDb, averageTime;

    cout << "Podaj tytul utworu: ";
    cin.ignore();
    getline(cin, title);

    cout << "Jaka jest ocena na IMDb w skali od 0 do 10? Podaj liczbe zmiennoprzecinkowa. ";
    ratingOnIMDb = validate<float>(10.0);

    cout << "Jakie gatunki filmowe posiada ten utwor? Wpisz liczbe i kliknij ENTER aby wpisac kolejna. Q aby wyjsc.\n" << endl;
    for( int i = 0; i < Utility::filmGenresNumber(); i ++ ) {
        cout << Utility::filmGenres()[i] << " - " << i << endl;
    }
    cout << "Q - wyjdz. ";

    // add genres
    while ( cin >> nr ) {
        if (nr[0] == 'q' || nr[0] == 'Q') {
            break;
        } else if (isdigit(nr[0])) {
            nrToInt = stoi(nr);
            if(nrToInt >= Utility::filmGenresNumber()) {
                cout << "Nie ma gatunku o numerze: " << nrToInt << endl;
            } else {
                // if there is no such position in film genres list,
                if(find(genres.begin(), genres.end(), Utility::filmGenres()[nrToInt]) != genres.end()) {
                    cout << "To video juz posiada taki gatunek! Wybierz inny.\n";
                } else { // add choosen position to it
                    genres.push_back(Utility::filmGenres()[nrToInt]);
                    cout << "Numer: " << nrToInt << " - gatunek: " << Utility::filmGenres()[nrToInt] << ". ";

                    // break if the list is full
                    if(genres.size() >= Utility::filmGenresNumber()) {
                        cout << "Wybrales wszystkie mozliwe gatunki." << endl;
                        break;
                    }

                    cout << endl;
                }
            }
        } else {
            cout << "Nieznana wartosc! Podaj jeszcze raz.\n" << endl;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

    }
    follow();

    this->title = title;
    this->ratingOnIMDb = ratingOnIMDb;
}

void Video::showInformation() {
    cout << "Tytul: " << title << endl;
    cout << "Ocena na IMDb: " << ratingOnIMDb << endl;
    cout << "Czy utwor jest sledzony? : ";
    if(isFollowed == 1) cout << "TAK" << endl;
    else cout << "NIE" << endl;
    cout << "Gatunki filmowe: ";
    for (int i = 0; i < genres.size(); i++ ) {
        cout << genres[i] << " ";
    }
    cout << endl;
}

void Video::follow() {
    char fav;
    bool isFollowed;
    cout << "Czy chcesz dodac utwor do ulubionych? (T/N)";
    cin >> fav;
    switch(fav) {
    case 'T':
        isFollowed = 1;
        break;
    case 'N':
        isFollowed = 0;
        break;
    default:
        cout << "Nieznana wartosc. Utwor nie bedzie sledzony. \n";
        isFollowed = 0;
        break;
    }

    this->isFollowed = isFollowed;
}

bool Video::isElemFollowed() {
    return isFollowed;
}
