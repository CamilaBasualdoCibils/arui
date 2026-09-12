#include "AruiServer.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    ARUI::AruiServer server(argc, argv);
    return server.Run();
}