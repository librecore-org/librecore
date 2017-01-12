#ifndef AMDFAM10_RESET_RAMSTAGE_H
#define AMDFAM10_RESET_RAMSTAGE_H

#include <stdint.h>

u32 get_sblk(void);
u8 get_sbbusn(u8 sblk);
void set_bios_reset(void);
u8 node_link_to_bus(u8 node, u8 link);

#endif
