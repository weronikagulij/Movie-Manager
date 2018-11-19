#include "Movie.h"
#include "validate.h"

string Movie::getType() {
    return "Movie";
}

void Movie::informationToText(string *data) {
    Video::informationToText(data);
    data[4] = to_string(rankingPosition);
}

void Movie::informationFromText(string *data) {
    Video::informationFromText(data);
    rankingPosition = stoi(data[4]);
}

void Movie::getRemainingTime(bool &hasElementExpirationTime, double &difference) {
    hasElementExpirationTime = false;
    difference = 0;
}

void Movie::fillInformation() {
    cout << "Utworzono nowy film.\n";
    Video::fillInformation();
    int rankingPosition;

    cout << "Jaka jest pozycja tego filmu na filmwebie? ";
    rankingPosition = validate<int>(-1);

    this->rankingPosition = rankingPosition;
}

void Movie::showInformation() {
    cout << "\n------\n";
    Video::showInformation();
    cout << "Pozycja filmu na filmwebie: " << rankingPosition << endl;
}

