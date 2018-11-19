#ifndef VALIDATE_H
#define VALIDATE_H

template<class T>
T validate(T a) {
    T pom = 0;
    string nr;

    while (getline(cin, nr)) {
        if (nr.length() > 6) {
            cout << "Za duza wartosc!" << endl;
        } else if(isdigit(nr[0])) {
            if(is_same<T, float>::value ) {
                pom = stof(nr);
            } else pom = stoi(nr);

            if(pom >= 0) {
                if ( a > -1 && pom <= a ) break;
                else if ( a == -1 ) break;
                else cout << "Wartosc musi miescic sie w przedziale: 0 - "<< a << endl;
            } else cout << "Wartosc musi byc dodatnia oraz calkowita.\n";
        } else {
            cout << "Wartosc musi byc dodatnia oraz calkowita.\n";
        }
    }
    return pom;
}

#endif
