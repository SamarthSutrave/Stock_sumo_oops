#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <iostream>

class Stock {
private:
    std::string symbol;
    std::string companyName;
    double currentPrice;
    double previousPrice;
    int volume;

public:
    // Constructors
    Stock();
    Stock(const std::string& symbol, const std::string& companyName, double price);

    // Getters
    std::string getSymbol() const;
    std::string getCompanyName() const;
    double getCurrentPrice() const;
    double getPreviousPrice() const;
    int getVolume() const;
    double getPriceChange() const;
    double getPriceChangePercentage() const;

    // Setters
    void setCurrentPrice(double price);
    void setVolume(int vol);

    // Utility functions
    void updatePrice(double newPrice);
    void displayInfo() const;

    // Operator overloading
    bool operator==(const Stock& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Stock& stock);
};

#endif
