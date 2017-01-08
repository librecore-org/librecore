/*
 * generic K8 debug code, used by mainboard specific romstage.c
 *
 */
#ifndef AMDK8_DEBUG_H
#define AMDK8_DEBUG_H

#include <inttypes.h>
#include "f.h"
#include "f_pci.h"

#if CONFIG_DEBUG_SMBUS
void dump_spd_registers(const struct mem_controller *ctrl);
void dump_smbus_registers(void);
#endif

#if CONFIG_K8_REV_F_SUPPORT
void dump_pci_device_index_wait(unsigned dev, uint32_t index_reg);
#endif

void print_debug_addr(const char *str, void *val);
void print_debug_pci_dev(unsigned dev);
void print_pci_devices(void);
void dump_pci_device(unsigned dev);
void dump_pci_devices(void);
void dump_pci_devices_on_bus(unsigned busn);
void dump_io_resources(unsigned port);
void dump_mem(unsigned start, unsigned end);

#endif
