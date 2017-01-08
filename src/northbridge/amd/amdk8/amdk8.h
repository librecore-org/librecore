#ifndef AMDK8_H
#define AMDK8_H

#include <arch/io.h>
#include <device/pci_def.h>
#include "raminit.h"

#ifdef __PRE_RAM__
struct mem_controller;
void showallroutes(int level, pci_devfn_t dev);
void setup_resource_map_offset(const unsigned int *register_values, int max, unsigned offset_pci_dev, unsigned offset_io_base);
void fill_mem_ctrl(int controllers, struct mem_controller *ctrl_a, const uint16_t *spd_addr);
#endif

void cpus_ready_for_init(void);
unsigned get_nodes(void);

#endif /* AMDK8_H */
