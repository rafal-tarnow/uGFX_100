#include <iostream>

#include <library_api/epoll.hpp>

#include "client_application.h"

using namespace std;

int main(int argc, char *argv[])
{
    Epoll epoll(false);
    ClientApplication client;
    epoll.runApp();

    cout << "EXIT_SUCESSFULL!" << endl;
    return 0;
}
