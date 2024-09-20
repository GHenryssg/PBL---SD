#ifndef I2C_H
#define I2C_H

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

// i2c base address
#define I2C_BASE 0xFFC04000
#define I2C_SPAN 0x00000100

// address of registers
#define I2C_CON 0x0
#define I2C_TAR 0x4
#define I2C_DATA_CMD 0x10
#define IC_FD_SCL_HCNT 0x1C
#define IC_FS_SCL_LCNT 0x20
#define IC_CLR_INTR 0x40
#define IC_ENABLE 0x6C
#define IC_TXFLR 0x74
#define IC_RXFLR 0x78
#define IC_ENABLE_STATUS 0x9C

// struct to hold mapped I2C register pointers
typedef struct {
    volatile int *i2c0_con;
    volatile int *i2c0_tar;
    volatile int *i2c0_data_cmd;
    volatile int *ic_fd_scl_hcnt;
    volatile int *ic_fs_scl_lcnt;
    volatile int *ic_clr_intr;
    volatile int *ic_enable;
    volatile int *ic_txflr;
    volatile int *ic_rxflr;
    volatile int *ic_enable_status;
} I2C_Registers;

int open_fd();

I2C_Registers map_i2c(int fd);

void unmap_i2c(void *i2c_virtual);

void I2C0_Init(I2C_Register *regs);

void Acelerometer_read_reg(I2C_Registers *regs, uint8_t address, uint8_t *value);

#endif