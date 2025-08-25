#ifndef MARKET_H
#define MARKET_H

#include <vector>
#include <map>
#include <string>
#include <random>
#include "Stock.h"

class Market {
private:
    std::vector<Stock> stocks;
    std::map<std::string, int> stockIndices; // symbol -> index mapping
    std::random_device rd;
    mutable std::mt19937 gen;  // Made mutable so it can be modified in const methods
    mutable std::uniform_real_distribution<> dis;  // Made mutable so it can be modified in const methods

public:
    // Constructors
    Market();

    // Stock management
    void addStock(const Stock& stock);
    void removeStock(const std::string& symbol);
    Stock* getStock(const std::string& symbol);
    std::vector<Stock> getAllStocks() const;

    // Market operations
    void simulateMarketUpdate();
    void updateStockPrice(const std::string& symbol, double newPrice);
    void displayMarket() const;
    void displayTopGainers() const;
    void displayTopLosers() const;

    // Search and filter
    std::vector<Stock> searchStocks(const std::string& query) const;
    std::vector<Stock> getStocksByPriceRange(double minPrice, double maxPrice) const;

    // Market statistics
    double getMarketCap() const;
    int getTotalStocks() const;

    // Initialize with sample stocks
    void initializeSampleStocks();

private:
    void buildStockIndex();
    double generateRandomPriceChange() const;  // Keep const but make gen and dis mutable
};

#endif