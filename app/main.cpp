#include "dispatcher.h"

int main()
{
    // ID=1, кол-во денег=10000, вероятность=0.10
    auto atm = std::make_shared<ATM>(1, 10000.0, 0.1);
    ATMDispatcher dispatcher(atm);
    dispatcher.start();
    return 0;
}