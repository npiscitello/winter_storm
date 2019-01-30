#ifndef RTC_REGDEF_H
#define RTC_REGDEF_H

// I2C Address (most significant 7 bits)
#define VAL_ADDR        0xD0
#define MSK_ADDR        0xFE
#define OFS_ADDR        1
#define VAL_WRITE       0x00
#define VAL_READ        0x01
#define MSK_RW          0x01
#define OFS_RW          0
#define VAL_ADDR_READ   (VAL_ADDR & MSK_ADDR) | (VAL_READ & MSK_RW)
#define VAL_ADDR_WRITE  (VAL_ADDR & MSK_ADDR) | (VAL_WRITE & MSK_RW)

// register definitions and bitmasks
#define REG_SEC         0x00
#define MSK_SEC_CH      0x80
#define OFS_SEC_CH      7
#define MSK_SEC_10      0x70
#define OFS_SEC_10      4
#define MSK_SEC_1       0x0F
#define OFS_SEC_1       0

#define REG_MIN         0x01
#define MSK_MIN_10      0x70
#define OFS_MIN_10      4
#define MSK_MIN_1       0x0F
#define OFS_MIN_1       0

#define REG_HOUR        0x02
#define MSK_HOUR_MODE   0x40
#define OFS_HOUR_MODE   6
#define MSK_12HOUR_AMPM 0x20
#define OFS_12HOUR_AMPM 5
#define MSK_12HOUR_10   0x10
#define MSK_24HOUR_10   0x30
#define OFS_HOUR_10     4
#define MSK_HOUR_1      0x0F
#define OFS_HOUR_1      0
#define MODE_12         0x01
#define MODE_24         0x00
#define VAL_AM          0x00
#define VAL_PM          0x01

#define REG_WDAY        0x03
#define MSK_WDAY_DAY    0x03
#define OFS_WDAY_DAY    0

#define REG_MDAY        0x04
#define MSK_MDAY_10     0x30
#define OFS_MDAY_10     4
#define MSK_MDAY_1      0x0F
#define OFS_MDAY_1      0

#define REG_MON         0x05
#define MSK_MON_10      0x10
#define OFS_MON_10      4
#define MSK_MON_1       0x0F
#define OFS_MON_1       0

#define REG_YEAR        0x06
#define MSK_YEAR_10     0xF0
#define OFS_YEAR_10     4
#define MSK_YEAR_1      0x0F
#define OFS_YEAR_1      0

#define REG_CTRL        0x07
#define MSK_CTRL_OUT    0x80
#define OFS_CTRL_OUT    7
#define MSK_CTRL_SQWE   0x10
#define OFS_CTRL_SQWE   4
#define MSK_CTRL_RS     0x30
#define OFS_CTRL_RS     0

// I2C Status Reg Values
#define MSK_STATUS      0xF8
#define STS_START       0x08
#define STS_RSTART      0x10
#define STS_SLAW_ACK    0x18
#define STS_SLAW_NACK   0x20
#define STS_DTRN_ACK    0x28
#define STS_DTRN_NACK   0x30
#define STS_ARB_LOST    0x38
#define STS_SLAR_ACK    0x40
#define STS_SLAR_NACK   0x48
#define STS_DRCV_ACK    0x50
#define STS_DRCV_NACK   0x58

#endif
