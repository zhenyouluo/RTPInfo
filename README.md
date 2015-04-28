# RTPInfo
Utility to tell you info about incoming RTP Stream (development heavily in progress)


###Example Output
```
~$ ./rtpParser
LISTENING ON: 8192
80 60 F7 35
15 8D 26 78
79 2D 5B 36
VERSION: 2
CONTAINS 0 CSRC identifiers
PAYLOAD TYPE: 96
SEQUENCE NUMBER: 63285
TIMESTAMP: 361571960
SSRC IDENTIFIER: 0
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
