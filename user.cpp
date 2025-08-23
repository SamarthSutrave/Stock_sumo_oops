#include "user.h"
#include <iostream>
//Used for formatting output (setw, setprecision, fixed).
#include <iomanip>
// Not directly used here (but could be useful for things like sorting later).
#include<algorithm>

using namespace std;
//default constructor
User::User() : username(""), email(""), virtualBalance(10000.0){}

// parametric construcort
User::User(const string& username, const string& email, double initialBalance)
    :username(username), email(email), virtualBalance(initialBalance){}

    //getters hgelps in grting th vl;ues for thr private varialbles const is used to make sure the function does not modify any member variables
string User::getUsername() const {return username;}
string User:: getEmail() const{return email;}
double User::getVirtualBalance() const { return virtualBalance;}
map<string, int> User:: getPortfolio() const {return portfolio;}
vector<string> User:: getTransactionHistory() const {return transactionHistory;}

//Acount Operations 
void User:: depositeVirtualMoney(double amount ){
    if(amount >0){
        virtualBalance+=amount;
        addTransaction("Deposited: $" + to_string(amount));
        cout<<"Deposited $"<< fixed<<setprecision(2)<<amount<<" successfully."<<endl;
    }
}//inv=cle the account balance is too low to add or buy the stock
bool User:: withdrawVirtualMoney(double amount){
    if(amount >0 && amount <= virtualBalance){
        virtualBalance -=amount;
        addTransaction("Withdrew: $"+ to_string(amount));
        cout<<"Withdrew $"<<fixed<<setprecision(2)<<amount<<" successfully."<<endl;
        return true;
    }else{
        cout<<"Insufficient balance or invalid amount."<<endl;
        return false;
    }
}
// trading ops 
bool User::buyStock(const Stock& stock ,int quantity){
if(totalcost >virtualBalance){
    cout<<"Insufficient balance to buy "<<quantity<<" shares of "<<stock.getSymbol()<<endl;
    return false;
}

    virtualBalance -= totalCost;
    portfolio[stock.getSymbol()] += quantity;

    string transaction = "BUY: " + to_string(quantity) + " shares of " +      stock.getSymbol() + " @ $" + to_string(stock.getCurrentPrice());
    addTransaction(transaction);

    cout << "Successfully bought " << quantity << " shares of " << stock.getSymbol()      << " for $" << fixed << setprecision(2) << totalCost << endl;
    return true;
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

void User::displayPortfolio(const vector<stock>& marketStocks) const {
    cout << "\n=== PORTFOLIO ===\n";
    if (portfolio.empty()) {
        cout << "No stocks in portfolio.\n";
        return;
    }

    double totalValue = 0.0;
    cout << left << setw(10) << "Symbol" << setw(10) << "Quantity" << setw(12) << "Price" << setw(12) << "Total Value" << endl;
    cout << "------------------------------------------------\n";

    for (const auto& holding : portfolio) {
        for (const auto& stock : marketStocks) {
            if (stock.getSymbol() == holding.first) {
                double stockValue = stock.getCurrentPrice() * holding.second;
                totalValue += stockValue;

                cout << left << setw(10) << holding.first  << setw(10) << holding.second << setw(12) << fixed << setprecision(2) << stock.getCurrentPrice() << setw(12) << stockValue << endl;
                break;
            }
        }
    }
    cout << "------------------------------------------------\n";
    cout << "Total Portfolio Value: $" << fixed << setprecision(2) << totalValue << endl;
}
Void User::displayTransactionHistory() const {
    cout << "\n=== TRANSACTION HISTORY ===\n";
    if (transactionHistory.empty()) {
        cout << "No transactions yet.\n";
        return;
    }
    for (size_t i=0;i<transactionHistory.size();++i){
        const string& transaction = transactionHistory[i];{
       // cout << transaction << endl;
    }
}
}
// Utility function 
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