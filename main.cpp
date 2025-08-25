#include <iostream>
#include <exception>
#include "TradingApp.h"

using namespace std;

int main() {
    try {
        // Create and run the trading application
        TradingApp app;
        app.run();
    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
        return 1;
    }

    return 0;
}
