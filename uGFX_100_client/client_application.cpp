#include "client_application.h"

#include <iostream>

using namespace std;

ClientApplication::ClientApplication()
{
    timer = new CTimer();
    timer->connect<ClientApplication, &ClientApplication::onTimer_100ms>(this);
    timer->start(100);
}

ClientApplication::~ClientApplication()
{
    delete timer;
}

void ClientApplication::onTimer_100ms()
{
    cout << "ClientApplication::onTimer_100ms()" << endl;
}
