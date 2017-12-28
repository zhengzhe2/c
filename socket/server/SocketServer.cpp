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
    m_isAccept = true;
    getData = NULL;
}


SocketServer::~SocketServer()
{
    finalServer();
    getData = NULL;
}

int SocketServer::receiveMsg(unsigned char *msg, int len)
{
    printf("receive Msg from client !!!!!!\n");
    int cnt;
    int rc;
    unsigned char* pch;
    pch = msg;
    cnt = len;
    while (cnt > 0 && m_connfd != INVALID_SOCKET) {
        rc = recv(m_connfd, pch, cnt, 0);
        if ( rc < 0) {
            if (errno == EINTR) {
                printf("socket connect normal !!!!!\n");
                rc = 0;
            }
            else {
                m_isAccept = true;
                closesocket(m_connfd);
                printf("recv failed, socket reconnect !!!!\n");
                return -1;
            }
        } else if (rc == 0) {
            m_isAccept = true;
            closesocket(m_connfd);
            printf("client close, socket reconnect !!!!\n");
            break;
        }else {
            cnt -= rc;
            pch += rc;
            if (*(pch-1) == '\0') {    //handle read() block by special character
                printf("data reception is completed!!!!\n");
                break;
            }
        }
    }
    return len - cnt - 1;
}

int SocketServer::sendMsg(const unsigned char *msg, int len)
{
    printf("send Msg to client !!!!!!!!!!\n");
    int cnt;
    int rc;
    const unsigned char* pch;
    pch = msg;
    cnt = len;
    while (cnt > 0 && m_connfd != INVALID_SOCKET) {
        if ( (rc = send(m_connfd, pch, cnt, 0)) <= 0) {
            if (rc < 0 && errno == EINTR) {
                rc = 0;
            }
            else {
                printf("send msg failed !!!!\n");
                return -1;
            }
        }
        cnt -= rc;
        pch += rc;
    }
    return len;
}

void SocketServer::registerGetData(fn_get_data callback)
{
    getData = callback;
}


void SocketServer::initServer()
{
    struct sockaddr_in servaddr;  //server address
    struct sockaddr_in  cliaddr;  //client address
    socklen_t cliaddr_len;
    unsigned char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    int bufLen;

    //init Socket
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == m_listenfd) {
        perr_exit("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULTPORT);

    if (bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        perr_exit("bind error");
    }

    if (listen(m_listenfd, THREADMAXSIZE) == SOCKET_ERROR) {
        perr_exit("listen error");
    }

    printf("Accepting connections ...\n");
    while (1) {
        if (m_isAccept) {
            m_isAccept = false;
            cliaddr_len = sizeof(cliaddr);
            m_connfd = accept(m_listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
            if (INVALID_SOCKET == m_connfd) {
                perr_exit("accept error");
            }
        }
        bufLen = receiveMsg(buf, BUFSIZ);
        printf("buf :%s   bufLen :%d  flag:%d \n", buf, bufLen, m_isAccept);
        getData(buf, bufLen);
    }
    closesocket(m_connfd);
}

void SocketServer::finalServer()
{
    closesocket(m_listenfd);
}



