#include "AruiServer.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    AruiServer server(argc, argv);
    return server.Run();
}