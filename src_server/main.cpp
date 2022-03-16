#include "Server.h"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: server <port> [<port> ...]\n";
            return 1;
        }
        int port = atoi(argv[1]);
        std::cout << "### RUN_SERVER / port " << port << std::endl;

        boost::asio::io_context io_context;
        Server server(io_context, port);
        io_context .run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }        

    return 0;
}
