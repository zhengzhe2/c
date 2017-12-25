#include "SocketServer.h"

int main()
{
    SocketServer* ser = new SocketServer();
    ser->initServer();
    return 0;
}
