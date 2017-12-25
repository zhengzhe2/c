#include "SocketServer.h"
#include "errno.h"

#define THREADMAXSIZE 10

static void perr_exit(const char* s)
{
    perror(s);
    exit(1);
}

SocketServer::SocketServer()
{
    m_listenfd = INVALID_SOCKET;
    m_connfd = INVALID_SOCKET;
    m_getData = NULL;
}


SocketServer::~SocketServer()
{
    finalServer();
    m_getData = NULL;
}

int SocketServer::receiveMsg(char *msg, int len)
{
    int cnt;
    int rc;
    char* pch;
    pch = msg;
    cnt = len;
    while (cnt > 0) {
        rc = read(m_connfd, pch, cnt);
        if ( rc < 0) {
            if (errno == EINTR) {
                rc = 0;
            }
            else {
                return -1;
            }
        } else if (rc == 0) {
            break;
        }else {
            cnt -= rc;
            pch += rc;
            if (*(pch-1) == '\0') {    //handle read() block by special character
                break;
            }
        }
    }
    return len - cnt - 1;
}

int SocketServer::sendMsg(const char *msg, int len)
{
    int cnt;
    int rc;
    const char* pch;
    pch = msg;
    cnt = len;
    while (cnt > 0) {
        if ( (rc = write(m_connfd, pch, cnt)) <= 0) {
            if (rc < 0 && errno == EINTR) {
                rc = 0;
            }
            else {
                return -1;
            }
        }
        cnt -= rc;
        pch += rc;
    }
    return len;
}

void SocketServer::registerGetDataCallback(fn_get_data_callback callback)
{
    m_getData = callback;
}

void SocketServer::initServer()
{
    struct sockaddr_in servaddr;  //server address
    struct sockaddr_in  cliaddr;  //client address
    socklen_t cliaddr_len;
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    int bufLen;

    //初始化Socket
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == m_listenfd) {
        perr_exit("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //设置的端口为DEFAULT_PORT。
    servaddr.sin_port = htons(DEFAULTPORT);

    //将本地地址绑定到所创建的套接字上
    if (bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        perr_exit("bind error");
    }

    if (listen(m_listenfd, THREADMAXSIZE) == SOCKET_ERROR) {
        perr_exit("listen error");
    }

    printf("Accepting connections ...\n");
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        m_connfd = accept(m_listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        if (INVALID_SOCKET == m_connfd) {
            perr_exit("accept error");
        }

        bufLen = receiveMsg(buf, BUFSIZ);
//        m_getData(buf, bufLen);
        sendMsg(buf, bufLen);
    }
    closesocket(m_connfd);
}

void SocketServer::finalServer()
{
    closesocket(m_listenfd);
}



