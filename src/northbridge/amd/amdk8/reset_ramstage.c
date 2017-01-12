#define __SIMPLE_DEVICE__

#include <stdint.h>
#include <cpu/x86/lapic.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include "raminit.h"
#include "reset_ramstage.h"

void set_bios_reset(void)
{
	u32 htic;
	htic = pci_read_config32(PCI_DEV(0, 0x18, 0), HT_INIT_CONTROL);
	htic &= ~HTIC_BIOSR_Detect;
	pci_write_config32(PCI_DEV(0, 0x18, 0), HT_INIT_CONTROL, htic);
}

unsigned node_link_to_bus(unsigned node, unsigned link)
{
	u8 reg;

	for (reg = 0xE0; reg < 0xF0; reg += 0x04) {
		u32 config_map;
		config_map = pci_read_config32(PCI_DEV(0, 0x18, 1), reg);
		if ((config_map & 3) != 3) {
			continue;
		}
		if ((((config_map >> 4) & 7) == node) &&
			(((config_map >> 8) & 3) == link))
		{
			return (config_map >> 16) & 0xff;
		}
	}
	return 0;
}

unsigned get_sblk(void)
{
	u32 reg;
	/* read PCI_DEV(0,0x18,0) 0x64 bit [8:9] to find out SbLink m */
	reg = pci_read_config32(PCI_DEV(0, 0x18, 0), 0x64);
	return ((reg>>8) & 3);
}

unsigned get_sbbusn(unsigned sblk)
{
	return node_link_to_bus(0, sblk);
}
