#include "User.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Default constructor
User::User() : username(""), email(""), virtualBalance(10000.0) {}

// Parameterized constructor
User::User(const string& username, const string& email, double initialBalance)
    : username(username), email(email), virtualBalance(initialBalance) {}

// Getters
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
double User::getVirtualBalance() const { return virtualBalance; }
map<string, int> User::getPortfolio() const { return portfolio; }
vector<string> User::getTransactionHistory() const { return transactionHistory; }

// Account operations
void User::depositVirtualMoney(double amount) {
    if (amount > 0) {
        virtualBalance += amount;
        addTransaction("Deposit: $" + to_string(amount));
        cout << "Deposited $" << fixed << setprecision(2) << amount << endl;
    }
}

bool User::withdrawVirtualMoney(double amount) {
    if (amount > 0 && amount <= virtualBalance) {
        virtualBalance -= amount;
        addTransaction("Withdrawal: $" + to_string(amount));
        cout << "Withdrawn $" << fixed << setprecision(2) << amount << endl;
        return true;
    }
    cout << "Insufficient funds for withdrawal." << endl;
    return false;
}

// Trading operations
bool User::buyStock(const Stock& stock, int quantity) {
    if (quantity <= 0) {
        cout << "Invalid quantity." << endl;
        return false;
    }

    double totalCost = stock.getCurrentPrice() * quantity;
    if (totalCost > virtualBalance) {
        cout << "Insufficient funds to buy " << quantity << " shares of " << stock.getSymbol() << endl;
        return false;
    }

    virtualBalance -= totalCost;
    portfolio[stock.getSymbol()] += quantity;

    string transaction = "BUY: " + to_string(quantity) + " shares of " + 
                         stock.getSymbol() + " @ $" + to_string(stock.getCurrentPrice());
    addTransaction(transaction);

    cout << "Successfully bought " << quantity << " shares of " << stock.getSymbol() 
              << " for $" << fixed << setprecision(2) << totalCost << endl;
    return true;
}

bool User::sellStock(const Stock& stock, int quantity) {
    if (quantity <= 0) {
        cout << "Invalid quantity." << endl;
        return false;
    }

    if (portfolio[stock.getSymbol()] < quantity) {
        cout << "Insufficient shares to sell." << endl;
        return false;
    }

    double totalRevenue = stock.getCurrentPrice() * quantity;
    virtualBalance += totalRevenue;
    portfolio[stock.getSymbol()] -= quantity;

    if (portfolio[stock.getSymbol()] == 0) {
        portfolio.erase(stock.getSymbol());
    }

    string transaction = "SELL: " + to_string(quantity) + " shares of " + 
                         stock.getSymbol() + " @ $" + to_string(stock.getCurrentPrice());
    addTransaction(transaction);

    cout << "Successfully sold " << quantity << " shares of " << stock.getSymbol() 
              << " for $" << fixed << setprecision(2) << totalRevenue << endl;
    return true;
}

// Portfolio operations
int User::getStockQuantity(const string& symbol) const {
    auto it = portfolio.find(symbol);
    return (it != portfolio.end()) ? it->second : 0;
}

double User::getPortfolioValue(const vector<Stock>& marketStocks) const {
    double totalValue = 0.0;
    for (const auto& holding : portfolio) {
        for (const auto& stock : marketStocks) {
            if (stock.getSymbol() == holding.first) {
                totalValue += stock.getCurrentPrice() * holding.second;
                break;
            }
        }
    }
    return totalValue;
}

void User::displayPortfolio(const vector<Stock>& marketStocks) const {
    cout << "\n=== PORTFOLIO ===\n";
    if (portfolio.empty()) {
        cout << "No stocks in portfolio.\n";
        return;
    }

    double totalValue = 0.0;
    cout << left << setw(10) << "Symbol" << setw(10) << "Quantity" 
              << setw(12) << "Price" << setw(12) << "Total Value" << endl;
    cout << "------------------------------------------------\n";

    for (const auto& holding : portfolio) {
        for (const auto& stock : marketStocks) {
            if (stock.getSymbol() == holding.first) {
                double stockValue = stock.getCurrentPrice() * holding.second;
                totalValue += stockValue;

                cout << left << setw(10) << holding.first 
                         << setw(10) << holding.second
                         << setw(12) << fixed << setprecision(2) << stock.getCurrentPrice()
                         << setw(12) << stockValue << endl;
                break;
            }
        }
    }
    cout << "------------------------------------------------\n";
    cout << "Total Portfolio Value: $" << fixed << setprecision(2) << totalValue << endl;
}

void User::displayTransactionHistory() const {
    cout << "\n=== TRANSACTION HISTORY ===\n";
    if (transactionHistory.empty()) {
        cout << "No transactions yet.\n";
        return;
    }

    for (size_t i = 0; i < transactionHistory.size(); ++i) {
        cout << (i + 1) << ". " << transactionHistory[i] << endl;
    }
}

// Utility functions
void User::addTransaction(const string& transaction) {
    transactionHistory.push_back(transaction);
}

void User::displayAccountInfo() const {
    cout << "\n=== ACCOUNT INFO ===\n";
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    cout << "Virtual Balance: $" << fixed << setprecision(2) << virtualBalance << endl;
}

void User::updateBalance(double amount) {
    virtualBalance += amount;
}
