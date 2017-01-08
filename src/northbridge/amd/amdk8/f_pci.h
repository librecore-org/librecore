#ifndef F_PCI_H
#define F_PCI_H

#include <inttypes.h>
#include <arch/io.h>
#include <device/pci_def.h>

uint32_t pci_read_config32_index_wait(pci_devfn_t dev,
		uint32_t index_reg, uint32_t index);

void pci_write_config32_index_wait(pci_devfn_t dev, uint32_t index_reg,
		uint32_t index, uint32_t data);

#endif
