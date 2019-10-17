#include "server_application.h"

#include <iostream>

#include "frame.hpp"

using namespace std;

Server::Server()
{
    timer = new CTimer();
    timer->connect<Server, &Server::onTimer_100ms>(this);
    timer->start(100);

   frame_init();
}

Server::~Server()
{
    delete timer;
}

void Server::onTimer_100ms()
{
    cout << "Zdarzenie Timera" << endl;
}

void Server::paintGL(int width, int height)
{
    frame_render(width, height);
}


