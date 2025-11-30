#include "dispatcher.h"

int main()
{
    auto cal = std::make_shared<Calendar>();
    CalendarDispatcher dispatcher(cal);
    dispatcher.start();
    return 0;
}