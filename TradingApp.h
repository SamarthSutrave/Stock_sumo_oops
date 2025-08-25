#ifndef TRADING_APP_H
#define TRADING_APP_H

#include "User.h"
#include "Market.h"
#include "Stock.h"
#include <memory>

class TradingApp {
private:
    std::unique_ptr<User> currentUser;
    Market market;
    bool isLoggedIn;

public:
    // Constructor and Destructor
    TradingApp();
    ~TradingApp();

    // Application lifecycle
    void run();
    void initialize();
    void shutdown();

    // User management
    bool login(const std::string& username, const std::string& email);
    void logout();
    bool registerUser(const std::string& username, const std::string& email, double initialBalance = 10000.0);

    // Main menu functions
    void displayMainMenu();
    void handleMainMenu();

    // Trading functions
    void displayTradingMenu();
    void handleTradingMenu();
    void buyStockInterface();
    void sellStockInterface();

    // Portfolio and account functions
    void displayPortfolioMenu();
    void handlePortfolioMenu();
    void showAccountInfo();
    void showPortfolio();
    void showTransactionHistory();
    void addFunds();
    void withdrawFunds();

    // Market functions
    void displayMarketMenu();
    void handleMarketMenu();
    void showMarketOverview();
    void searchStocks();
    void showTopGainersLosers();
    void simulateMarketUpdate();

    // Utility functions
    void clearScreen();
    void pauseScreen();
    int getMenuChoice(int minChoice, int maxChoice);
    double getPositiveDouble(const std::string& prompt);
    int getPositiveInt(const std::string& prompt);
    std::string getString(const std::string& prompt);

private:
    void displayWelcome();
    void displayGoodbye();
};

#endif
