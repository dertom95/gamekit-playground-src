#ifndef WSOCKET_H
#define WSOCKET_H
/*=========================================================================*\
* Socket compatibilization module for Win32
* LuaSocket toolkit
\*=========================================================================*/

/*=========================================================================*\
* WinSock include files
\*=========================================================================*/
#define _WIN32_WINNT 0x0501
#define LUASOCKET_INET_PTON 1
#include <winsock2.h>
#include <ws2tcpip.h>

typedef int socklen_t;
typedef SOCKADDR_STORAGE t_sockaddr_storage;
typedef SOCKET t_socket;
typedef t_socket *p_socket;

#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY 27
#endif

#define SOCKET_INVALID (INVALID_SOCKET)

#ifndef SO_REUSEPORT
#define SO_REUSEPORT SO_REUSEADDR
#endif

#ifndef AI_NUMERICSERV
#define AI_NUMERICSERV (0)
#endif

#endif /* WSOCKET_H */
