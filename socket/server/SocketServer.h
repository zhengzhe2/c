#ifndef SOCKETSERVER
#define SOCKETSERVER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define DEFAULTPORT 6666
#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (-1)
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR    (-1)
#endif
#ifndef closesocket
#define closesocket(x)  ::close(x)
#endif

typedef void (*fn_get_data)(unsigned char* data, int len);

class SocketServer
{
public:
    SocketServer();
    ~SocketServer();
    void initServer();
    void finalServer();
    int sendMsg(const unsigned char* msg, int len);
    void registerGetData(fn_get_data callback);
private:
    int receiveMsg(unsigned char* msg, int len);

private:
    int m_listenfd;
    int m_connfd;
    bool m_isAccept;
    fn_get_data getData;
};

#endif // SERVER

