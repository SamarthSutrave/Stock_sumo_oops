#include "TradingApp.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// Constructor and Destructor
TradingApp::TradingApp() : currentUser(nullptr), isLoggedIn(false) {}

TradingApp::~TradingApp() {
    shutdown();
}

// Application lifecycle
void TradingApp::run() {
    initialize();
    displayWelcome();

    while (true) {
        if (!isLoggedIn) {
            cout << "\n1. Login\n2. Register\n3. Exit\n";
            int choice = getMenuChoice(1, 3);

            switch (choice) {
                case 1: {
                    string username = getString("Enter username: ");
                    string email = getString("Enter email: ");
                    login(username, email);
                    break;
                }
                case 2: {
                    string username = getString("Enter username: ");
                    string email = getString("Enter email: ");
                    double initialBalance = getPositiveDouble("Enter initial virtual balance (default $10000): ");
                    if (initialBalance == 0) initialBalance = 10000.0;
                    registerUser(username, email, initialBalance);
                    break;
                }
                case 3:
                    displayGoodbye();
                    return;
            }
        } else {
            handleMainMenu();
        }
    }
}

void TradingApp::initialize() {
    cout << "Initializing Trading App...\n";
    market.initializeSampleStocks();
    cout << "Trading App initialized successfully!\n";
}

void TradingApp::shutdown() {
    if (isLoggedIn) {
        logout();
    }
    cout << "Trading App shutdown completed.\n";
}

// User management
bool TradingApp::login(const string& username, const string& email) {
    // In a real application, this would validate against a database
    currentUser = make_unique<User>(username, email, 10000.0);
    isLoggedIn = true;
    cout << "\nWelcome back, " << username << "!\n";
    pauseScreen();
    return true;
}

void TradingApp::logout() {
    if (isLoggedIn) {
        cout << "\nGoodbye, " << currentUser->getUsername() << "!\n";
        currentUser.reset();
        isLoggedIn = false;
    }
}

bool TradingApp::registerUser(const string& username, const string& email, double initialBalance) {
    currentUser = make_unique<User>(username, email, initialBalance);
    isLoggedIn = true;
    cout << "\nRegistration successful! Welcome, " << username << "!\n";
    pauseScreen();
    return true;
}

// Main menu functions
void TradingApp::displayMainMenu() {
    clearScreen();
    cout << "\n=== VIRTUAL STOCK TRADING APP ===\n";
    cout << "User: " << currentUser->getUsername() << "\n";
    cout << "Balance: $" << fixed << setprecision(2) << currentUser->getVirtualBalance() << "\n";
    cout << "\n1. Trading\n";
    cout << "2. Portfolio\n";
    cout << "3. Market Overview\n";
    cout << "4. Account Settings\n";
    cout << "5. Logout\n";
    cout << "\nSelect an option: ";
}

void TradingApp::handleMainMenu() {
    displayMainMenu();
    int choice = getMenuChoice(1, 5);

    switch (choice) {
        case 1:
            handleTradingMenu();
            break;
        case 2:
            handlePortfolioMenu();
            break;
        case 3:
            handleMarketMenu();
            break;
        case 4:
            showAccountInfo();
            pauseScreen();
            break;
        case 5:
            logout();
            break;
    }
}

// Trading functions
void TradingApp::displayTradingMenu() {
    clearScreen();
    cout << "\n=== TRADING MENU ===\n";
    cout << "1. Buy Stock\n";
    cout << "2. Sell Stock\n";
    cout << "3. View Market\n";
    cout << "4. Search Stocks\n";
    cout << "5. Back to Main Menu\n";
    cout << "\nSelect an option: ";
}

void TradingApp::handleTradingMenu() {
    displayTradingMenu();
    int choice = getMenuChoice(1, 5);

    switch (choice) {
        case 1:
            buyStockInterface();
            break;
        case 2:
            sellStockInterface();
            break;
        case 3:
            showMarketOverview();
            pauseScreen();
            break;
        case 4:
            searchStocks();
            pauseScreen();
            break;
        case 5:
            return;
    }
    if (choice != 5) {
        handleTradingMenu();
    }
}

void TradingApp::buyStockInterface() {
    showMarketOverview();
    string symbol = getString("\nEnter stock symbol to buy: ");
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    Stock* stock = market.getStock(symbol);
    if (!stock) {
        cout << "Stock not found!\n";
        pauseScreen();
        return;
    }

    stock->displayInfo();
    int quantity = getPositiveInt("Enter quantity to buy: ");

    if (currentUser->buyStock(*stock, quantity)) {
        cout << "Purchase successful!\n";
    } else {
        cout << "Purchase failed!\n";
    }
    pauseScreen();
}

void TradingApp::sellStockInterface() {
    currentUser->displayPortfolio(market.getAllStocks());

    if (currentUser->getPortfolio().empty()) {
        cout << "No stocks to sell!\n";
        pauseScreen();
        return;
    }

    string symbol = getString("\nEnter stock symbol to sell: ");
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    Stock* stock = market.getStock(symbol);
    if (!stock) {
        cout << "Stock not found!\n";
        pauseScreen();
        return;
    }

    int currentQuantity = currentUser->getStockQuantity(symbol);
    if (currentQuantity == 0) {
        cout << "You don't own any shares of " << symbol << "!\n";
        pauseScreen();
        return;
    }

    cout << "You own " << currentQuantity << " shares of " << symbol << "\n";
    stock->displayInfo();

    int quantity = getPositiveInt("Enter quantity to sell: ");

    if (currentUser->sellStock(*stock, quantity)) {
        cout << "Sale successful!\n";
    } else {
        cout << "Sale failed!\n";
    }
    pauseScreen();
}

// Portfolio and account functions
void TradingApp::displayPortfolioMenu() {
    clearScreen();
    cout << "\n=== PORTFOLIO MENU ===\n";
    cout << "1. View Portfolio\n";
    cout << "2. Transaction History\n";
    cout << "3. Add Funds\n";
    cout << "4. Withdraw Funds\n";
    cout << "5. Account Information\n";
    cout << "6. Back to Main Menu\n";
    cout << "\nSelect an option: ";
}

void TradingApp::handlePortfolioMenu() {
    displayPortfolioMenu();
    int choice = getMenuChoice(1, 6);

    switch (choice) {
        case 1:
            showPortfolio();
            pauseScreen();
            break;
        case 2:
            showTransactionHistory();
            pauseScreen();
            break;
        case 3:
            addFunds();
            break;
        case 4:
            withdrawFunds();
            break;
        case 5:
            showAccountInfo();
            pauseScreen();
            break;
        case 6:
            return;
    }
    if (choice != 6) {
        handlePortfolioMenu();
    }
}

void TradingApp::showAccountInfo() {
    clearScreen();
    currentUser->displayAccountInfo();
    cout << "Total Portfolio Value: $" << fixed << setprecision(2) 
              << currentUser->getPortfolioValue(market.getAllStocks()) << "\n";
}

void TradingApp::showPortfolio() {
    clearScreen();
    currentUser->displayPortfolio(market.getAllStocks());
}

void TradingApp::showTransactionHistory() {
    clearScreen();
    currentUser->displayTransactionHistory();
}

void TradingApp::addFunds() {
    double amount = getPositiveDouble("Enter amount to deposit: $");
    currentUser->depositVirtualMoney(amount);
    pauseScreen();
}

void TradingApp::withdrawFunds() {
    double amount = getPositiveDouble("Enter amount to withdraw: $");
    currentUser->withdrawVirtualMoney(amount);
    pauseScreen();
}

// Market functions
void TradingApp::displayMarketMenu() {
    clearScreen();
    cout << "\n=== MARKET MENU ===\n";
    cout << "1. Market Overview\n";
    cout << "2. Search Stocks\n";
    cout << "3. Top Gainers/Losers\n";
    cout << "4. Simulate Market Update\n";
    cout << "5. Back to Main Menu\n";
    cout << "\nSelect an option: ";
}

void TradingApp::handleMarketMenu() {
    displayMarketMenu();
    int choice = getMenuChoice(1, 5);

    switch (choice) {
        case 1:
            showMarketOverview();
            pauseScreen();
            break;
        case 2:
            searchStocks();
            pauseScreen();
            break;
        case 3:
            showTopGainersLosers();
            pauseScreen();
            break;
        case 4:
            simulateMarketUpdate();
            pauseScreen();
            break;
        case 5:
            return;
    }
    if (choice != 5) {
        handleMarketMenu();
    }
}

void TradingApp::showMarketOverview() {
    clearScreen();
    market.displayMarket();
    cout << "\nTotal Stocks: " << market.getTotalStocks() << "\n";
}

void TradingApp::searchStocks() {
    string query = getString("Enter search term (symbol or company name): ");
    auto results = market.searchStocks(query);

    if (results.empty()) {
        cout << "No stocks found matching '" << query << "'\n";
    } else {
        cout << "\nSearch results for '" << query << "':\n";
        for (const auto& stock : results) {
            stock.displayInfo();
        }
    }
}

void TradingApp::showTopGainersLosers() {
    clearScreen();
    market.displayTopGainers();
    market.displayTopLosers();
}

void TradingApp::simulateMarketUpdate() {
    market.simulateMarketUpdate();
}

// Utility functions
void TradingApp::clearScreen() {
    // Cross-platform screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void TradingApp::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int TradingApp::getMenuChoice(int minChoice, int maxChoice) {
    int choice;
    while (!(cin >> choice) || choice < minChoice || choice > maxChoice) {
        cout << "Invalid choice. Please enter a number between " 
                 << minChoice << " and " << maxChoice << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Clear the newline character
    return choice;
}

double TradingApp::getPositiveDouble(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cout << "Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return value;
}

int TradingApp::getPositiveInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value <= 0) {
        cout << "Please enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return value;
}

string TradingApp::getString(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Private methods
void TradingApp::displayWelcome() {
    clearScreen();
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║           VIRTUAL STOCK TRADING APP             ║\n";
    cout << "  ║                                                  ║\n";
    cout << "  ║        🚀 Trade with Virtual Money 🚀           ║\n";
    cout << "  ║                                                  ║\n";
    cout << "  ║  • Buy and sell stocks with virtual money       ║\n";
    cout << "  ║  • Track your portfolio performance             ║\n";
    cout << "  ║  • Monitor real-time market changes             ║\n";
    cout << "  ║  • Learn trading without financial risk         ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    cout << "\n";
    pauseScreen();
}

void TradingApp::displayGoodbye() {
    clearScreen();
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║                 THANK YOU!                      ║\n";
    cout << "  ║                                                  ║\n";
    cout << "  ║     Thanks for using Virtual Stock Trading App  ║\n";
    cout << "  ║             Happy Trading! 📈                   ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    cout << "\n";
}
