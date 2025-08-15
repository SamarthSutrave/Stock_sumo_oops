#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>
#include "Stock.h"
// using name spacestd is not good practice 
class User {
private:
// private data to hide

    std::string username;
    std::string email;
    double virtualBalance;
    std::map<std::string, int> portfolio; // symbol -> quantity
    std::vector<std::string> transactionHistory;

public:
    // Constructors
    User();
    //parametarized constructor
    
    User(const std::string& username, const std::string& email, double initialBalance = 10000.0);

    // Getters
    std::string getUsername() const;
    std::string getEmail() const;
    double getVirtualBalance() const;
    std::map<std::string, int> getPortfolio() const;
    std::vector<std::string> getTransactionHistory() const;

    // Account operations
    void depositVirtualMoney(double amount);
    bool withdrawVirtualMoney(double amount);

    // Trading operations
    bool buyStock(const Stock& stock, int quantity);
    bool sellStock(const Stock& stock, int quantity);

    // Portfolio operations
    int getStockQuantity(const std::string& symbol) const;
    double getPortfolioValue(const std::vector<Stock>& marketStocks) const;
    void displayPortfolio(const std::vector<Stock>& marketStocks) const;
    void displayTransactionHistory() const;

    // Utility functions
    void addTransaction(const std::string& transaction);
    void displayAccountInfo() const;

private:
    void updateBalance(double amount);
};

#endif
