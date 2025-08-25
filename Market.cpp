#include "Market.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// Constructor
Market::Market() : gen(rd()), dis(-0.05, 0.05) {
    // Initialize random number generator
    gen.seed(static_cast<unsigned int>(time(nullptr)));
}

// Stock management
void Market::addStock(const Stock& stock) {
    stocks.push_back(stock);
    buildStockIndex();
}

void Market::removeStock(const string& symbol) {
    auto it = remove_if(stocks.begin(), stocks.end(),
                            [&symbol](const Stock& stock) {
                                return stock.getSymbol() == symbol;
                            });
    stocks.erase(it, stocks.end());
    buildStockIndex();
}

Stock* Market::getStock(const string& symbol) {
    auto it = stockIndices.find(symbol);
    if (it != stockIndices.end()) {
        return &stocks[it->second];
    }
    return nullptr;
}

vector<Stock> Market::getAllStocks() const {
    return stocks;
}

// Market operations
void Market::simulateMarketUpdate() {
    cout << "\n--- Market Update ---\n";
    for (auto& stock : stocks) {
        double currentPrice = stock.getCurrentPrice();
        double changePercent = generateRandomPriceChange();
        double newPrice = currentPrice * (1.0 + changePercent);

        // Ensure price doesn't go below $1
        if (newPrice < 1.0) {
            newPrice = 1.0 + (currentPrice * 0.01);
        }

        stock.updatePrice(newPrice);

        // Simulate volume changes
        int newVolume = uniform_int_distribution<>(1000, 100000)(gen);
        stock.setVolume(newVolume);
    }
    cout << "Market prices updated!\n";
}

void Market::updateStockPrice(const string& symbol, double newPrice) {
    Stock* stock = getStock(symbol);
    if (stock && newPrice > 0) {
        stock->updatePrice(newPrice);
        cout << "Updated " << symbol << " price to $" << fixed << setprecision(2) << newPrice << endl;
    } else {
        cout << "Stock not found or invalid price." << endl;
    }
}

void Market::displayMarket() const {
    cout << "\n=== STOCK MARKET ===\n";
    cout << left << setw(8) << "Symbol" << setw(20) << "Company" 
              << setw(12) << "Price" << setw(12) << "Change" << setw(10) << "Change%" << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (const auto& stock : stocks) {
        cout << left << setw(8) << stock.getSymbol()
                 << setw(20) << stock.getCompanyName().substr(0, 19)
                 << setw(12) << fixed << setprecision(2) << stock.getCurrentPrice()
                 << setw(12) << showpos << stock.getPriceChange()
                 << setw(10) << noshowpos << stock.getPriceChangePercentage() << "%"
                 << endl;
    }
    cout << "-----------------------------------------------------------------------\n";
}

void Market::displayTopGainers() const {
    vector<Stock> sortedStocks = stocks;
    sort(sortedStocks.begin(), sortedStocks.end(),
             [](const Stock& a, const Stock& b) {
                 return a.getPriceChangePercentage() > b.getPriceChangePercentage();
             });

    cout << "\n=== TOP GAINERS ===\n";
    int count = min(5, static_cast<int>(sortedStocks.size()));
    for (int i = 0; i < count; ++i) {
        const auto& stock = sortedStocks[i];
        cout << (i + 1) << ". " << stock.getSymbol() << " - "
                 << fixed << setprecision(2) << stock.getPriceChangePercentage() << "%\n";
    }
}

void Market::displayTopLosers() const {
    vector<Stock> sortedStocks = stocks;
    sort(sortedStocks.begin(), sortedStocks.end(),
             [](const Stock& a, const Stock& b) {
                 return a.getPriceChangePercentage() < b.getPriceChangePercentage();
             });

    cout << "\n=== TOP LOSERS ===\n";
    int count = min(5, static_cast<int>(sortedStocks.size()));
    for (int i = 0; i < count; ++i) {
        const auto& stock = sortedStocks[i];
        cout << (i + 1) << ". " << stock.getSymbol() << " - "
                 << fixed << setprecision(2) << stock.getPriceChangePercentage() << "%\n";
    }
}

// Search and filter
vector<Stock> Market::searchStocks(const string& query) const {
    vector<Stock> results;
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& stock : stocks) {
        string lowerSymbol = stock.getSymbol();
        string lowerCompany = stock.getCompanyName();
        transform(lowerSymbol.begin(), lowerSymbol.end(), lowerSymbol.begin(), ::tolower);
        transform(lowerCompany.begin(), lowerCompany.end(), lowerCompany.begin(), ::tolower);

        if (lowerSymbol.find(lowerQuery) != string::npos ||
            lowerCompany.find(lowerQuery) != string::npos) {
            results.push_back(stock);
        }
    }
    return results;
}

vector<Stock> Market::getStocksByPriceRange(double minPrice, double maxPrice) const {
    vector<Stock> results;
    for (const auto& stock : stocks) {
        if (stock.getCurrentPrice() >= minPrice && stock.getCurrentPrice() <= maxPrice) {
            results.push_back(stock);
        }
    }
    return results;
}

// Market statistics
double Market::getMarketCap() const {
    double totalCap = 0.0;
    for (const auto& stock : stocks) {
        totalCap += stock.getCurrentPrice() * stock.getVolume();
    }
    return totalCap;
}

int Market::getTotalStocks() const {
    return static_cast<int>(stocks.size());
}

// Initialize with sample stocks
void Market::initializeSampleStocks() {
    stocks.clear();

    // Add sample stocks
    addStock(Stock("AAPL", "Apple Inc.", 150.25));
    addStock(Stock("GOOGL", "Alphabet Inc.", 2500.75));
    addStock(Stock("MSFT", "Microsoft Corporation", 300.50));
    addStock(Stock("AMZN", "Amazon.com Inc.", 3200.25));
    addStock(Stock("TSLA", "Tesla Inc.", 250.75));
    addStock(Stock("META", "Meta Platforms Inc.", 320.50));
    addStock(Stock("NVDA", "NVIDIA Corporation", 450.25));
    addStock(Stock("NFLX", "Netflix Inc.", 400.75));
    addStock(Stock("DIS", "Walt Disney Company", 95.25));
    addStock(Stock("UBER", "Uber Technologies", 42.50));

    // Set initial volumes
    uniform_int_distribution<> volumeDist(10000, 500000);
    for (auto& stock : stocks) {
        stock.setVolume(volumeDist(gen));
    }

    buildStockIndex();
    cout << "Sample stocks initialized successfully!\n";
}

// Private methods
void Market::buildStockIndex() {
    stockIndices.clear();
    for (size_t i = 0; i < stocks.size(); ++i) {
        stockIndices[stocks[i].getSymbol()] = static_cast<int>(i);
    }
}

double Market::generateRandomPriceChange() const {
    return dis(gen);
}
