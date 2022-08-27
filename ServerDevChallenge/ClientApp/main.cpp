#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "HeaderFiles/Client.h"
#include "SourceFiles/Client.cpp"
using namespace std;
Client x;
void my_function(int sig)
{
    std::cout << "Receving Signal " << std::endl;
    exit(0);
}
int main()
{
    signal(SIGINT, my_function);
    x.MainLoop();
    return 0;
}
