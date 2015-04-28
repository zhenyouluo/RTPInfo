#include <cstdio>
#include <cstdlib>
#include <cstring>
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

// only what I care about for now
enum PayloadType {
    PCMU=0,
    GSM=3,
    G723=4,
    DVI4=5, // or 6 or 16 or 17
    JPEG=26,
    // A/V are dynamic, 96-127 range
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

    puts("LISTENING ON: 8192");
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
            printf("%02X %02X %02X %02X\n", buf[8],buf[9],buf[10],buf[11]);

            // unsure about mixing masks & bitshifts here.

            packet.version = buf[0] >> 6;       // 2 bits
            packet.padding = buf[0] & 0x20;     // 1 bit
            packet.extension = buf[0] & 0x10;   // 1 bit
            packet.csrc_count = buf[0] & 0xF;   // 4 bits

            packet.marker = buf[1] >> 7;                    // 1 bit
            packet.payload_type = buf[1] & 0xFF;            // 7 bits
            packet.sequence_number = buf[2] << 8 | buf[3];  // 16 bits

            // have to verify endianness here
            // might actually be the other way around!
            packet.timestamp = buf[4] << 24 | buf[5] << 16 | buf[6] << 8 | buf[7];


            switch (packet.version) {
                case 0: 
                    puts("VERSION: VAT");
                    break;
                case 1:
                    puts("VERSION: RTP DRAFT");
                    break;
                default:
                    printf("VERSION: %u\n", packet.version);
                    break;
            }

            if (packet.padding != 0) {
                puts("HAS PADDING");
            }

            if (packet.extension != 0) {
                puts("HAS EXTENSION HEADER");
            }

            printf("CONTAINS %"PRIu32" CSRC identifiers\n", packet.csrc_count);

            if (packet.marker != 0) {
                puts("MARKER IS SET");
            }

            switch (packet.payload_type) {
                case 0:
                    puts("PAYLOAD TYPE: PCMU");
                    break;
                case 1:
                    puts("PAYLOAD TYPE: reserved");
                    break;
                case 2:
                    puts("PAYLOAD TYPE: reserved");
                    break;
                case 3:
                    puts("PAYLOAD TYPE: GSM");
                    break;
                case 4:
                    puts("PAYLOAD TYPE: G723");
                    break;
                case 5:
                    puts("PAYLOAD TYPE: DVI4");
                    break;
                case 6:
                    puts("PAYLOAD TYPE: DVI4");
                    break;
                case 7:
                    puts("PAYLOAD TYPE: LPC");
                    break;
                case 8:
                    puts("PAYLOAD TYPE: PCMA");
                    break;
                default:
                    printf("PAYLOAD TYPE: %"PRIu32"\n",packet.payload_type);
                    break;
            }

            printf("SEQUENCE NUMBER: %"PRIu32"\n", packet.sequence_number);

            printf("TIMESTAMP: %"PRIu32"\n", packet.timestamp);

            printf("SSRC IDENTIFIER: %"PRIu32"\n", packet.syncronization_source);
        }
 //   }
}
