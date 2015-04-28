# RTPInfo
Utility to tell you info about incoming RTP Stream (development heavily in progress)


###Example Output
```
~$ ./rtpParser
LISTENING ON: 8192
80 60 88 96
34 AD 1E 55
71 88 26 B5
VERSION: 2
CONTAINS 0 CSRC identifiers
PAYLOAD TYPE: 96
SEQUENCE NUMBER: 34966
TIMESTAMP: 883760725
SSRC IDENTIFIER: 1904748213
```

###Info

RTP Header has minimum size of 12 octets, with prelude, timestamp, ssrc identifier, followed by optional trailing info.

```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           synchronization source (SSRC) identifier            |
   +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
   |            contributing source (CSRC) identifiers             |
   |                             ....                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

####Versions   
* Current RTP Version is 2.
* Version 1 is Draft
* Version 0 is VAT Audio tool protocol


###Initial Values
* Initial timestamp is random (RFC 1889 and RFC 3550)
* Initial SEQ is random (RFC 1889 and RFC 3550)

####Additional Material
* [RFC 3550](https://tools.ietf.org/html/rfc3550)
* [RFC 3551](https://tools.ietf.org/html/rfc3551)
* [RFC 6184](https://tools.ietf.org/html/rfc6184)
* [RFC 6416](https://tools.ietf.org/html/rfc6416)
