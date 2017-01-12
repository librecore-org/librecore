#ifndef AMDFAM10_RESET_TEST_H
#define AMDFAM10_RESET_TEST_H

#include <stdint.h>

#ifdef __PRE_RAM__
u32 cpu_init_detected(u8 nodeid);
u32 bios_reset_detected(void);
u32 cold_reset_detected(void);
u32 other_reset_detected(void);
u32 warm_reset_detect(u8 nodeid);
void distinguish_cpu_resets(u8 nodeid);
#endif

u32 get_sblk(void);
u8 get_sbbusn(u8 sblk);
void set_bios_reset(void);

#endif
