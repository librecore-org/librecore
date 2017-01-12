/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define __SIMPLE_DEVICE__

#include <arch/io.h>
#include <stdint.h>
#include <northbridge/amd/amdfam10/raminit.h>
#include <northbridge/amd/amdfam10/amdfam10.h>
#include "reset_ramstage.h"

void set_bios_reset(void)
{

	u32 nodes;
	u32 htic;
	pci_devfn_t dev;
	int i;

	nodes = ((pci_read_config32(PCI_DEV(CONFIG_CBB, CONFIG_CDB, 0), 0x60) >> 4) & 7) + 1;

	for (i = 0; i < nodes; i++) {
		dev = NODE_PCI(i,0);
		htic = pci_read_config32(dev, HT_INIT_CONTROL);
		htic &= ~HTIC_BIOSR_Detect;
		pci_write_config32(dev, HT_INIT_CONTROL, htic);
	}
}

u32 get_sblk(void)
{
	u32 reg;
	/* read PCI_DEV(CONFIG_CBB,CONFIG_CDB,0) 0x64 bit [8:9] to find out SbLink m */
	reg = pci_io_read_config32(PCI_DEV(CONFIG_CBB, CONFIG_CDB, 0), 0x64);
	return ((reg>>8) & 3);
}

u8 get_sbbusn(u8 sblk)
{
	return node_link_to_bus(0, sblk);
}

u8 node_link_to_bus(u8 node, u8 link) // node are 6 bit, and link three bit
{
	u32 reg;
	u32 val;

	// put node and link in correct bit
	val = ((node & 0x0f)<<4) | ((node & 0x30)<< (12-4)) | ((link & 0x07)<<8);

	for (reg = 0xE0; reg < 0xF0; reg += 0x04) {
		u32 config_map;
		config_map = pci_io_read_config32(PCI_DEV(CONFIG_CBB, CONFIG_CDB, 1), reg);
		if ((config_map & 3) != 3) {
			continue;
		}
		if ((config_map & (((63 & 0x0f)<<4) | ((63 & 0x30)<< (12-4)) | ((7 & 0x07)<<8))
			) == val)
		{
			return (config_map >> 16) & 0xff;
		}
	}

	return 0;
}
