#ifndef RTP_TYPES_H_
#define RTP_TYPES_H_

#include <cstdint>
#include <cstddef>

namespace rtpinfo {

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

}

#endif