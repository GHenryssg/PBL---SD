#include <stdio.h>
#include "i2c.c"
#include "i2c.h"

int main() {
    int fd;
    I2C_Registers regs;
    int16_t mg_per_lbs = 4;
    int16_t X[2];
    fd = open_fd();

    regs = map_i2c(fd);

    I2C0_Init(&regs);

    while (1)
    {
        if(accelereometer_isDataReady(regs)) {
            accelerometer_x_read(X, regs);
            printf("X = %d mg\n", X[0]*mg_per_lbs);
        }
    }

    return 0;
}