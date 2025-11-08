#pragma once
#include <iostream>

class ATM;

// Abstract State class
class ATMState
{
public:
    virtual ~ATMState() = default;
    virtual void enterPIN(ATM *, int) { std::cout << "Action not allowed in current state.\n"; }
    virtual void withdraw(ATM *, double) { std::cout << "Action not allowed in current state.\n"; }
    virtual void finish(ATM *) { std::cout << "Action not allowed in current state.\n"; }
    virtual void loadMoney(ATM *, double) { std::cout << "Action not allowed in current state.\n"; }
    virtual const char *name() const = 0;
};

class WaitingState : public ATMState
{
public:
    const char *name() const override { return "Waiting"; }

    void enterPIN(ATM *atm, int pin) override;
    void loadMoney(ATM *atm, double amount) override;
};

class AuthenticationState : public ATMState
{
public:
    const char *name() const override { return "Authentication"; }

    void enterPIN(ATM *atm, int pin) override;
};

class OperationsState : public ATMState
{
public:
    const char *name() const override { return "Operations"; }

    void withdraw(ATM *atm, double amount) override;
    void finish(ATM *atm) override;
};

class BlockedState : public ATMState
{
public:
    const char *name() const override { return "Blocked"; }

    void loadMoney(ATM *atm, double amount) override;
};