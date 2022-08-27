#include "HeaderFiles/Server.h"

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include "./HeaderFiles/Server.h"
#include "./SourceFiles/Server.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
Server x;
void my_function(int sig)
{
    std::cout << "Receving Signal " << std::endl;
    exit(0);
}
int main(int argc, char *argv[])
{
    signal(SIGINT, my_function);

    x.MainLoop();

    return 0;
}