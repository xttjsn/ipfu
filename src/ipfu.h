#pragma once

#define IPHDR_FLAG_INIT 0
#define IPHDR_FLAG_DONT_FRAG(flg) (flg | (1 << 1))
#define IPHDR_FLAG_MAY_FRAG(flg) (flg & ~(1 << 1))
#define IPHDR_FLAG_LAST_FRAG(flg) (flg & ~(1 << 2))
#define IPHDR_FLAG_LAST_FRAG(flg) (flg | (1 << 2))

#define OPT_CLS_CTRL      0
#define OPT_CLS_RSV0      1
#define OPT_CLS_DBG_MSR   2
#define OPT_CLS_RSV1      3

#define OPT_CPD_NOT       0
#define OPT_CPD_CPD       1

struct iphdr {
	unsigned char ihl : 4,    // Internet Header Length in 32 bit
				  // words, points to beginning of data
   		ver : 4,	  // Version number, rfc791 uses 4
		tos;		  // Type of Service, see rfc791 for details
	unsigned short len;       // Total length. Length of the datagram
				  // measured in bytes, including internet
				  // header and data. Up to 2^16-1
				  // bytes. All hosts must accept up to 576
				  // bytes datagrams.
	unsigned short id;	  // Identification
	unsigned short foff : 13, // Fragment offset. Indicates where
				  // in this datagram this fragment
				  // belongs.
		flag : 3;         // Various control flags
	unsigned char tol;        // Maximum time the datagram is
                                  // allowed to remain. Unit is second.
        unsigned char protocol;   // The protocol number in the next
                                  // level. See rfc790. TCP is 6.
        unsigned short hdrcksm;   // Header checksum. Algorithm: the
                                  // 16 bit one's complement of the
                                  // one's complement sum of all 16
                                  // bit words in the header. For
                                  // purpose of computing the
                                  // checksum, the value of checksum
                                  // field is zero.
        unsigned int src;         // Source address.
        unsigned int dst;         // Destination address.
};

struct ipopt_type {
        unsigned char cpd:1,      // Copied flag
                cls:2,            // Option class
                num:5;            // Option number
};

struct ipopt {
        struct ipopt_type type;   // Option type
        unsigned char len;        // Option length
        unsigned char* data;      // Option data, NULL means it's the
                                  // first type option, see rfc791 for
                                  // details
};

/**
 * Define internet options as described in rfc791
 **/

#define OPT_END_OF_LIST             0
#define OPT_NO_OP                   1
#define OPT_SECURITY                ((1 << 7) | (1 << 1))            // Type 130
#define OPT_LSRR                    ((1 << 7) | (1 << 1) | (1 << 0)) // Type 131
#define OPT_STRICT_SRC_ROUTING      (9 << 3)
#define OPT_RECORD_ROUTE            (7)                              // Type 7
#define OPT_STREAM_ID               ((1 << 7) | (1 << 3))            // Type 136
#define OPT_TIMESTAMP               ((2 << 1) | (4 << 3))

#define OPT_LEN_SECURITY            11
#define OPT_LEN_STREAM_ID           4

#define OPT_SECURITY_UNCLASSIFIED   0
#define OPT_SECURITY_CONFIDENTIAL   61749    // 0b11110001 00110101
#define OPT_SECURITY_EFTO           30874    // 0b01111000 10011010
#define OPT_SECURITY_MMMM           48205    // 0b10111100 01001101
#define OPT_SECURITY_PROG           24102    // 0b01011110 00100110
#define OPT_SECURITY_RESTRICTED     44819    // 0b10101111 00010011
#define OPT_SECURITY_SECRET         55176    // 0b11010111 10001000
#define OPT_SECURITY_TOP_SECRET     27589    // 0b01101011 11000101

#define OPT_SECURITY_COMPARTMENTS   0        // See DIA for values
#define OPT_SECURITY_HANDLING_RESTRICTION 0
#define OPT_SECURITY_TCC            0        // See HQ DCA Code 530
