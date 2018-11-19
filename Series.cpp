#include "Series.h"
#include "validate.h"

string Series::getType() {
    return "Series";
}

void Series::informationToText(string *data) {
    Video::informationToText(data);
    data[4] = to_string(howManyEpisodes);
}

void Series::informationFromText(string *data) {
    Video::informationFromText(data);
    howManyEpisodes = stoi(data[4]);
}

void Series::getRemainingTime(bool &hasElementExpirationTime, double &difference) {
    hasElementExpirationTime = false;
    difference = 0;
}

void Series::fillInformation() {
    cout << "Utworzono nowy serial.\n";
    Video::fillInformation();
    int howManyEpisodes;

    cout << "Jak wiele odcinkow posiada ten serial? ";
    howManyEpisodes = validate<int>(-1);

    this->howManyEpisodes = howManyEpisodes;
}

void Series::showInformation() {
    cout << "\n------\n";
    Video::showInformation();
    cout << "Serial posiada: " << howManyEpisodes << " odcinkow." << endl;
}

