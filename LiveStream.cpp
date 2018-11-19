#include "LiveStream.h"
#include "time.h"
#include "validate.h"

string LiveStream::getType() {
    return "LiveStream";
}

void LiveStream::informationToText(string *data) {
    data[4] = to_string(startDate->tm_year + 1900);
    data[5] = to_string(startDate->tm_mon + 1);
    data[6] = to_string(startDate->tm_mday);
    data[7] = to_string(startDate->tm_hour);
    data[8] = to_string(startDate->tm_min);
}

void LiveStream::informationFromText(string *data) {
    Video::informationFromText(data);

    time_t now;
    time ( &now );
    startDate = localtime ( &now );

    startDate->tm_sec = 0;
    startDate->tm_min = stoi(data[8]);
    startDate->tm_hour = stoi(data[7]);
    startDate->tm_mday = stoi(data[6]);
    startDate->tm_mon = stoi(data[5]) - 1;
    startDate->tm_year = stoi(data[4]) - 1900;


}

LiveStream::~LiveStream() {
    delete startDate;
    //delete remainingTime;
}

void LiveStream::fillInformation() {
    cout << "Utworzono nowy live stream.\n";
    Video::fillInformation();
    int tm_min, tm_hour, tm_mday, tm_mon, tm_year;
    cout << "Podaj ROK rozpoczecia: ";
    tm_year = validate<int>(3000);

    cout << "Podaj MIESIAC rozpoczecia: ";
    tm_mon = validate<int>(12);

    cout << "Podaj DZIEN rozpoczecia: ";
    tm_mday = validate<int>(31);

    cout << "Podaj GODZINE rozpoczecia: ";
    tm_hour = validate<int>(23);

    cout << "Podaj MINUTE rozpoczecia: ";
    tm_min = validate<int>(59);

    time_t now;
    time ( &now );
    startDate = localtime ( &now );

    startDate->tm_sec = 0;
    startDate->tm_min = tm_min;
    startDate->tm_hour = tm_hour;
    startDate->tm_mday = tm_mday;
    startDate->tm_mon = tm_mon - 1;
    startDate->tm_year = tm_year - 1900;
}

void LiveStream::showInformation() {
    cout << "\n\n------\n";
    Video::showInformation();
    cout << "Data rozpoczecia live streamu: "
    << startDate->tm_year + 1900 << "-" << startDate->tm_mon + 1 << "-" << startDate->tm_mday
    << " godz. " << startDate->tm_hour << ":" << startDate->tm_min << endl;
}

void LiveStream::getRemainingTime(bool &hasElementExpirationTime, double &difference) {
    time_t t = time(0);
    int days, hours, minutes, seconds;
    difference = difftime(mktime(startDate), t);
    hasElementExpirationTime = true;
}

