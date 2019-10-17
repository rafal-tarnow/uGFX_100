#pragma once

#include <library_api/ctimer.h>

class ClientApplication
{
public:
    ClientApplication();
    ~ClientApplication();
    void onTimer_100ms();
private:
   CTimer * timer = nullptr;
};


