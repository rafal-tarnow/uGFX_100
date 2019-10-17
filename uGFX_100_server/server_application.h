#pragma once

#include <library_api/ctimer.h>

class Server
{
public:
    Server();
    ~Server();
    void onTimer_100ms();
    void paintGL(int width, int height);
private:
    CTimer * timer;
};


