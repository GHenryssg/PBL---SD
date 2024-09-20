#include "i2c.h"

// opem memory file
int open_fd() {
    int fd = open("/dev/mem", (O_RDWR | O_SYNC));
    if (fd == -1) {
        printf("didn`t open /dev/mem\n");
    }

    return fd;
}

// map I2C registers into virtual address space and return a struct with pointers
I2C_Registers map_i2c(int fd) {
    I2C_Registers regs;
    void *i2c_virtual = mmap(NULL, I2C_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, I2C_BASE);

        if (i2c_virtual == MAP_FAILED) {
            printf("error when mapping\n");
            close(fd);
            //return null pointers in case error
            regs.i2c0_con = NULL;
            return regs;
        }

        // map each registers into the struct
    regs.i2c0_con = (int *)(i2c_virtual + I2C_CON);
    regs.i2c0_tar = (int *)(i2c_virtual + I2C_TAR);
    regs.i2c0_data_cmd = (int *)(i2c_virtual + I2C_DATA_CMD);
    regs.ic_fd_scl_hcnt = (int *)(i2c_virtual + IC_FD_SCL_HCNT);
    regs.ic_fs_scl_lcnt = (int *)(i2c_virtual + IC_FS_SCL_LCNT);
    regs.ic_clr_intr = (int *)(i2c_virtual + IC_CLR_INTR);
    regs.ic_enable = (int *)(i2c_virtual + IC_ENABLE);
    regs.ic_txflr = (int *)(i2c_virtual + IC_TXFLR);
    regs.ic_rxflr = (int *)(i2c_virtual + IC_RXFLR);
    regs.ic_enable_status = (int *)(i2c_virtual + IC_ENABLE_STATUS);
    
    return regs;
}

// unmap I2C memory and close file descriptor
void unmap_i2c(void *i2c_virtual) {
    if (munmap(i2c_virtual, I2C_SPAN) != 0) {
        printf("error when unmapping\n");
    }
}

// I2C inicialization function 
void I2C_Init(I2C_Registers *regs) {
    // abort ongoing transmits and disable I2C0
    *regs->ic_enable = 2;

    // wait until I2C0 is disable 
    while ((*regs->ic_enable_status & 0x1) == 1) {}

    // configure the config register (master mode, 7-bit addressing, fast mode)
    *regs->i2c0_con = 0x65;

    // set target address (7-bit addressing)
    *regs->i2c0_tar = 0x53;

    // set SCL high/low counts for fast mode (400kHz)

    *regs->ic_fd_scl_hcnt = 60 + 30; // SCl high period (0.6us + 0.3us)
    *regs->ic_fs_scl_lcnt = 130 + 30; // SCL low period (1.3us + 0.3us)

    // enable the I2C controller
    *regs->ic_enable = 1;

    //wait until the controller is powered on 
    while ((*regs->ic_enable_status & 0x1) == 0) {}
}

