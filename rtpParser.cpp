#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <inttypes.h>

const int MAXBUFLEN = 1500;


struct RTPPacket {
    uint32_t version                : 2; 
    uint32_t padding                : 1;
    uint32_t extension              : 1;
    uint32_t csrc_count             : 4;
    uint32_t marker                 : 1;
    uint32_t payload_type           : 7;
    uint32_t sequence_number        : 16;
    uint32_t timestamp              : 32;
    uint32_t syncronization_source  : 32;
};

int main(void) {
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int sock;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;


    if ((rv = getaddrinfo("172.16.1.34", "14902", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
    }
    else {
        puts("GOT ADDRINFO");
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            fprintf(stderr, "talker: socket");
            continue;
         }

        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock);
            fprintf(stderr, "talker: failed to bind socket\n");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "talker: failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    int numbytes;
    struct sockaddr_storage remote_addr;
    uint8_t buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    addr_len = sizeof(remote_addr);
    
    RTPPacket packet;
    unsigned i = 0;
//    for (;;) {
        if ((numbytes = recvfrom(sock, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&remote_addr, &addr_len)) == -1) {
                fprintf(stderr, "error receiving data");
                exit(EXIT_FAILURE);
            }
        else {
            printf("%02X %02X %02X %02X\n", buf[0],buf[1],buf[2],buf[3]);
            printf("%02X %02X %02X %02X\n", buf[4],buf[5],buf[6],buf[7]);
            uint32_t timestamp = (((buf[4] | (buf[5] << 8)) | (buf[6] << 0x10)) | (buf[7] << 0x18));
            printf("%02X %02X %02X %02X\n", buf[8],buf[9],buf[10],buf[11]);

            unsigned version = buf[0] >> 6;  // 2 bits
            unsigned padding = buf[0] & 0x20;  // 1 bit
            unsigned extension = buf[0] & 0x10; // 1 bit
            unsigned csrc_count = buf[0] & 0xF;  // 4 bits

            switch (version) {
                case 0: 
                    puts("VERSION: VAT");
                    break;
                case 1:
                    puts("VERSION: RTP DRAFT");
                    break;
                default:
                    printf("VERSION: %u\n", version);
                    break;
            }
        }
 //   }
}
