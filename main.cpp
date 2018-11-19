#include <iostream>
#include "AppManager.h"

using namespace std;

int main()
{
	try {
    	AppManager app;
    	app.startApp();
    }
	catch (string msg) {
		cout << "Pojawil sie blad... " << msg;
	}
    return 0;
}
