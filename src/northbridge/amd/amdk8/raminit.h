#ifndef RAMINIT_H
#define RAMINIT_H

#define K8_REV_F_SUPPORT_F0_F1_WORKAROUND 0

#define NODE_NUMS 8
#define TIMEOUT_LOOPS 300000

#define DIMM_SOCKETS 4
struct mem_controller {
	unsigned node_id;
	pci_devfn_t f0, f1, f2, f3;
	uint16_t channel0[DIMM_SOCKETS];
	uint16_t channel1[DIMM_SOCKETS];
};

#include "f.h"

extern struct sys_info sysinfo_car;

void exit_from_self(int controllers, const struct mem_controller *ctrl, struct sys_info *sysinfo);
void setup_resource_map(const unsigned int *register_values, int max);
void set_sysinfo_in_ram(unsigned val);
void train_ram_on_node(unsigned nodeid, unsigned coreid, struct sys_info *sysinfo, unsigned retcall);
void sdram_set_registers(const struct mem_controller *ctrl, struct sys_info *sysinfo);
void sdram_set_spd_registers(const struct mem_controller *ctrl,
				     struct sys_info *sysinfo);
void sdram_enable(int controllers, const struct mem_controller *ctrl,
			  struct sys_info *sysinfo);

#if defined(__PRE_RAM__) && CONFIG_RAMINIT_SYSINFO
void sdram_initialize(int controllers, const struct mem_controller *ctrl, void *sysinfo);
#else
void sdram_initialize(int controllers, const struct mem_controller *ctrl);
#endif

extern int spd_read_byte(unsigned device, unsigned address);
extern void activate_spd_rom(const struct mem_controller *ctrl);
extern void memreset(int controllers, const struct mem_controller *ctrl);

#if K8_REV_F_SUPPORT_F0_F1_WORKAROUND == 1
void dqs_timing(int controllers, const struct mem_controller *ctrl, tsc_t *tsc0, struct sys_info *sysinfo);
#else
void dqs_timing(int controllers, const struct mem_controller *ctrl, struct sys_info *sysinfo);
#endif

void set_hw_mem_hole(int controllers, const struct mem_controller *ctrl);
void dqs_restore_MC_NVRAM(unsigned int dev);
void setup_mtrr_dqs(unsigned tom_k, unsigned tom2_k);
void clear_mtrr_dqs(unsigned tom2_k);

#endif /* RAMINIT_H */
