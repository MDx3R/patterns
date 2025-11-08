#pragma once
#include <random>
#include "state.h"

class ATM
{
private:
    int id;
    double totalMoney;
    double connectionFailureProb;
    std::unique_ptr<ATMState> currentState;

    bool tryConnection() const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen) > connectionFailureProb;
    }

public:
    ATM(int id, double money, double prob);

    void enterPIN(int pin);
    void withdraw(double amount);
    void finish();
    void loadMoney(double amount);

    bool hasConnection() const { return tryConnection(); }

    double getTotalMoney() const { return totalMoney; }
    int getId() const { return id; }

    void addMoney(double amount) { totalMoney += amount; }
    void deductMoney(double amount) { totalMoney -= amount; }

    void setState(std::unique_ptr<ATMState> newState);
    ATMState *getState() const { return currentState.get(); }

    void reportNoConnection() const
    {
        std::cout << "No connection with the bank. Try again later.\n";
    }
};

ATM::ATM(int id, double money, double prob)
    : id(id),
      totalMoney(money),
      connectionFailureProb(prob),
      currentState(std::make_unique<WaitingState>()) {}

void ATM::setState(std::unique_ptr<ATMState> newState)
{
    std::cout << "Transition: " << currentState->name() << " to " << newState->name() << "\n";
    currentState = std::move(newState);
}

void ATM::enterPIN(int pin)
{
    if (!hasConnection())
        return reportNoConnection();
    currentState->enterPIN(this, pin);
}

void ATM::withdraw(double amount)
{
    if (!hasConnection())
        return reportNoConnection();
    currentState->withdraw(this, amount);
}

void ATM::finish()
{
    currentState->finish(this);
}

void ATM::loadMoney(double amount)
{
    currentState->loadMoney(this, amount);
}

void WaitingState::enterPIN(ATM *atm, int pin)
{
    atm->setState(std::make_unique<AuthenticationState>());
    atm->enterPIN(pin);
}

void WaitingState::loadMoney(ATM *atm, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }
    atm->addMoney(amount);
    std::cout << "Money loaded. Total: " << atm->getTotalMoney() << "\n";
}

void AuthenticationState::enterPIN(ATM *atm, int pin)
{
    if (pin == 1234)
    {
        std::cout << "PIN correct.\n";
        atm->setState(std::make_unique<OperationsState>());
    }
    else
    {
        std::cout << "Incorrect PIN. Returning to waiting.\n";
        atm->setState(std::make_unique<WaitingState>());
    }
}

void OperationsState::withdraw(ATM *atm, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }
    if (amount > atm->getTotalMoney())
    {
        std::cout << "Insufficient funds.\n";
        return;
    }

    atm->deductMoney(amount);
    std::cout << "Withdrawn: " << amount << ", Remaining: " << atm->getTotalMoney() << "\n";

    if (atm->getTotalMoney() == 0)
    {
        std::cout << "ATM is out of money. Blocking.\n";
        atm->setState(std::make_unique<BlockedState>());
    }
}

void OperationsState::finish(ATM *atm)
{
    std::cout << "Session finished.\n";
    atm->setState(std::make_unique<WaitingState>());
}

void BlockedState::loadMoney(ATM *atm, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }

    atm->addMoney(amount);
    std::cout << "Money loaded. Total: " << atm->getTotalMoney() << "\n";

    if (atm->getTotalMoney() > 0)
    {
        atm->setState(std::make_unique<WaitingState>());
    }
}