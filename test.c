#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <sys/capability.h>

int main() {
        int packet_sock = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_IP));
        if (packet_sock < 0) {
                printf("fail to create packet socket.");
                return -1;
        }

        struct sockaddr_ll src_addr;
        socklen_t addr_len = sizeof src_addr;
        unsigned char dest[] = {'\x52', '\x54', '\x00', '\x89', '\xe2', '\xf0'};

        memset((void*)&src_addr, 0, addr_len);
        src_addr.sll_family = AF_PACKET;
        src_addr.sll_protocol = htons(ETH_P_IP);
        src_addr.sll_ifindex = 2; // 0 for any interfac, 1 for lo, 2 for eth0
        src_addr.sll_halen = ETH_ALEN; // Ethernet address, or MAC address
        memcpy((void*)(src_addr.sll_addr), (void*)dest, ETH_ALEN);

        char buffer[2048];

        unsigned int n = recvfrom(packet_sock, buffer, 2048, 0,
                                  (struct sockaddr*)&src_addr, &addr_len);

        printf("%x", buffer);
}
