#include <stdint.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D
#define XYZ_DATA_CFG 0x0E
#define WHOAMI 0x1A

void read_full_x(void);
extern int16_t acc_X;
void Delay (uint32_t dly);

int16_t get_acc_X(void);

void showX(void);
