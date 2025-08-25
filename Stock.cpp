#include "Stock.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Default constructor
Stock::Stock() : symbol(""), companyName(""), currentPrice(0.0), previousPrice(0.0), volume(0) {}

// Parameterized constructor
Stock::Stock(const string& symbol, const string& companyName, double price) 
    : symbol(symbol), companyName(companyName), currentPrice(price), previousPrice(price), volume(0) {}

// Getters
string Stock::getSymbol() const { return symbol; }
string Stock::getCompanyName() const { return companyName; }
double Stock::getCurrentPrice() const { return currentPrice; }
double Stock::getPreviousPrice() const { return previousPrice; }
int Stock::getVolume() const { return volume; }

double Stock::getPriceChange() const {
    return currentPrice - previousPrice;
}

double Stock::getPriceChangePercentage() const {
    if (previousPrice == 0) return 0.0;
    return ((currentPrice - previousPrice) / previousPrice) * 100.0;
}

// Setters
void Stock::setCurrentPrice(double price) { 
    previousPrice = currentPrice;
    currentPrice = price; 
}

void Stock::setVolume(int vol) { volume = vol; }

// Utility functions
void Stock::updatePrice(double newPrice) {
    previousPrice = currentPrice;
    currentPrice = newPrice;
}

void Stock::displayInfo() const {
    cout << fixed << setprecision(2);
    cout << "Symbol: " << symbol << "\n";
    cout << "Company: " << companyName << "\n";
    cout << "Current Price: $" << currentPrice << "\n";
    cout << "Price Change: $" << getPriceChange() << " (" << getPriceChangePercentage() << "%)\n";
    cout << "Volume: " << volume << "\n";
    cout << "------------------------\n";
}

// Operator overloading
bool Stock::operator==(const Stock& other) const {
    return symbol == other.symbol;
}

ostream& operator<<(ostream& os, const Stock& stock) {
    os << stock.symbol << " - $" << fixed << setprecision(2) << stock.currentPrice;
    return os;
}
