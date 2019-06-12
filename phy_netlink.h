/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
#ifndef __PHY_NETLINK_H
#define __PHY_NETLINK_H

#ifndef u8
typedef unsigned char u8;
#endif

/* Genetlink setup */
enum {
	PHYNL_CMD_NOOP,
	PHYNL_CMD_CABDIAG,

	__PHYNL_CMD_CNT,
	PHYNL_CMD_MAX = (__PHYNL_CMD_CNT - 1)
};

enum {
	CABDIAG_OP_ATTR_NOOP,
	CABDIAG_OP_ATTR_REQUEST,

	__CABDIAG_OP_ATTR_CNT,
	CABDIAG_OP_ATTR_MAX = (__CABDIAG_OP_ATTR_CNT - 1)
};

enum {
        CABDIAG_PAIR_STA_ATTR_NOOP,
        CABDIAG_PAIR_STA_ATTR_STATUS,
        CABDIAG_PAIR_STA_ATTR_LENGTH,

        __CABDIAG_PAIR_STA_ATTR_CNT,
        CABDIAG_PAIR_STA_ATTR_MAX = (__CABDIAG_PAIR_STA_ATTR_CNT - 1)
};

enum {
        CABDIAG_REQ_ATTR_NOOP,
        CABDIAG_REQ_ATTR_IFNAME,
        CABDIAG_REQ_ATTR_OP_STA,
        CABDIAG_REQ_ATTR_PAIRS_MASK,
        CABDIAG_REQ_ATTR_TIMEOUT,
        CABDIAG_REQ_ATTR_STATUS,

        __CABDIAG_REQ_ATTR_CNT,
        CABDIAG_REQ_ATTR_MAX = (__CABDIAG_REQ_ATTR_CNT - 1)
};

/* phy.h definitions */
#define CABDIAG_PAIR_A_MASK 0x0001
#define CABDIAG_PAIR_B_MASK 0x0002
#define CABDIAG_PAIR_C_MASK 0x0004
#define CABDIAG_PAIR_D_MASK 0x0008
enum phy_cabdiag_pairs {
	CABDIAG_PAIR_A,
	CABDIAG_PAIR_B,
	CABDIAG_PAIR_C,
	CABDIAG_PAIR_D,

	CABDIAG_PAIR_CNT,
};

/**
 * phy_cabdiag_op_sta - Cable diagnostics operational status
 * CD_REQ_NONE                    - Unknow
 * CD_REQ_INVALID_PAIR_MASK       - Invalid pair mask
 * CD_REQ_INVALID_TIMEOUT         - Invalid Timeout counter
 * CD_REQ_REJECTED_BUSY           - Previous command execusion busy
 * CD_STATUS_SUCCESS              - Operation success
 * CD_STATUS_FAILED_TIMEOUT       - Failed due to Timeout
 * CD_STATUS_FAILED_INVALID       - Status results invalid
 */
enum phy_cabdiag_op_sta {
        CD_REQ_NONE,
        CD_REQ_INVALID_PAIR_MASK,
        CD_REQ_INVALID_TIMEOUT,
        CD_REQ_REJECTED_BUSY,
        CD_STATUS_SUCCESS,
        CD_STATUS_FAILED_TIMEOUT,
        CD_STATUS_FAILED_INVALID
};

#define CD_NOT_SUPPORTED 0xFF

/**
 * phy_cabdiag_sta_code - Cable diagnostics fault codes
 * b0000 - 0100: Individual cable pair fault codes
 * b10xx       : Cross pair short to pair 'xx'
 * b11xx       : Abnormal Cross pair coupling with pair 'xx'
 *    xx       : b00 - Pair-A,
 *             : b01 - Pair-B,
 *             : b10 - Pair-C,
 *             : b11 - Pair-D
 */
enum phy_cabdiag_sta_code {
	CD_NORMAL_PAIR            = 0x0,
	CD_OPEN_PAIR              = 0x1,
	CD_SHORTED_PAIR           = 0x2,
	CD_ABNORMAL_TERMINATION   = 0x4,
	CD_X_PAIR_SHORT_TO_PAIR_A = 0x8,
	CD_X_PAIR_SHORT_TO_PAIR_B = 0x9,
	CD_X_PAIR_SHORT_TO_PAIR_C = 0xA,
	CD_X_PAIR_SHORT_TO_PAIR_D = 0xB,
	CD_ABNORMAL_X_PAIR_A      = 0xC,
	CD_ABNORMAL_X_PAIR_B      = 0xD,
	CD_ABNORMAL_X_PAIR_C      = 0xE,
	CD_ABNORMAL_X_PAIR_D      = 0xF,
	CD_NOT_SUPPORT            = 0xFF
};

/**
 * struct phy_cabdiag_pair_sta - PHY diagnostics pair status
 * @status: Fault codes
 * @length: Length in meters
 */
struct phy_cabdiag_pair_sta {
        enum phy_cabdiag_sta_code status;
        u8 length;
};

/**
 * struct phy_cabdiag_req - PHY diagnostics request/status command
 * @op_status: Cable Diagnostics Operational status
 * @pairs_bitmask: Allows settings diag request just for a pair
 * @timeout: Timeout count (i.e. Multiples of driver wait time)
 * @pairs[CABDIAG_PAIR_CNT]: Status of 4 pairs of cable
 */
struct phy_cabdiag_req {
        enum phy_cabdiag_op_sta op_status;
        u8 pairs_bitmask;
        u8 timeout_cnt;
        struct phy_cabdiag_pair_sta pairs[CABDIAG_PAIR_CNT];
};

#endif /* __PHY_NETLINK_H */
