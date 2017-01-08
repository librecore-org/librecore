#ifndef RESET_TEST_H
#define RESET_TEST_H

#include <stdint.h>

#define NODE_ID		0x60
#define	HT_INIT_CONTROL 0x6c

#define HTIC_ColdR_Detect  (1<<4)
#define HTIC_BIOSR_Detect  (1<<5)
#define HTIC_INIT_Detect   (1<<6)

int cpu_init_detected(unsigned nodeid);
int bios_reset_detected(void);
int cold_reset_detected(void);
void distinguish_cpu_resets(unsigned nodeid);
void set_bios_reset(void);
unsigned node_link_to_bus(unsigned node, unsigned link);
unsigned get_sblk(void);
unsigned get_sbbusn(unsigned sblk);

#endif
