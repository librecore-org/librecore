/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 AMD
 * (Written by Yinghai Lu <yinghailu@amd.com> for AMD)
 * Copyright (C) 2007 Philipp Degler <pdegler@rumms.uni-mannheim.de>
 * (Thanks to LSRA University of Mannheim for their support)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* Used by ite_enable_serial(). */
#define SERIAL_DEV PNP_DEV(0x2e, IT8712F_SP1)
#define CLKIN_DEV PNP_DEV(0x2e, IT8712F_GPIO)

#include <stdint.h>
#include <string.h>
#include <device/pci_def.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <device/pci_ids.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8712f/it8712f.h>
#include <cpu/amd/model_fxx_rev.h>
#include <console/console.h>
#include <southbridge/nvidia/ck804/early_smbus.h>
#include <reset.h>
#include <timestamp.h>
#include <cpu/amd/model_fxx/init_cpus.h>
#include <northbridge/amd/amdk8/ht.h>
#include <northbridge/amd/amdk8/raminit.h>
#include <northbridge/amd/amdk8/early_ht.h>
#include <delay.h>
#include <cpu/amd/mtrr.h>
#include <cpu/amd/car.h>
#include <cpu/amd/microcode.h>
#include <cpu/x86/bist.h>
#include "northbridge/amd/amdk8/setup_resource_map.c"
#include <southbridge/nvidia/ck804/early_setup_ss.h>
#include <spd.h>

unsigned int get_sbdn(unsigned bus)
{
	pci_devfn_t dev;

	dev = pci_locate_device_on_bus(PCI_ID(PCI_VENDOR_ID_NVIDIA,
				PCI_DEVICE_ID_NVIDIA_CK804_PRO), bus);
	return (dev >> 15) & 0x1f;
}

void memreset(int controllers, const struct mem_controller *ctrl) { }
void activate_spd_rom(const struct mem_controller *ctrl) { }

int spd_read_byte(unsigned device, unsigned address)
{
	return smbus_read_byte(device, address);
}

#include "lib/generic_sdram.c"
#include "cpu/amd/dualcore/dualcore.c"
#include "southbridge/nvidia/ck804/early_setup.c"

static void sio_setup(void)
{
	uint32_t dword;
	uint8_t byte;

	/* Subject decoding */
	byte = pci_read_config8(PCI_DEV(0, CK804_DEVN_BASE + 1, 0), 0x7b);
	byte |= 0x20;
	pci_write_config8(PCI_DEV(0, CK804_DEVN_BASE + 1, 0), 0x7b, byte);

	/* LPC Positive Decode 0 */
	dword = pci_read_config32(PCI_DEV(0, CK804_DEVN_BASE + 1, 0), 0xa0);
	dword |= (1 << 0) | (1 << 1);	/* Serial 0, Serial 1 */
	pci_write_config32(PCI_DEV(0, CK804_DEVN_BASE + 1, 0), 0xa0, dword);
}

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	struct sys_info *sysinfo = &sysinfo_car;

	static const uint16_t spd_addr[] = {
		DIMM0, DIMM2, 0, 0,
		DIMM1, DIMM3, 0, 0,
#if CONFIG_MAX_PHYSICAL_CPUS > 1
		DIMM4, DIMM6, 0, 0,
		DIMM5, DIMM7, 0, 0,
#endif
	};

	int needs_reset;
	unsigned nodes, bsp_apicid = 0;

	if (!cpu_init_detectedx && boot_cpu()) {
		/* Nothing special needs to be done to find bus 0 */
		/* Allow the HT devices to be found */
		enumerate_ht_chain();
		sio_setup();
	}

	if (bist == 0)
		bsp_apicid = init_cpus(cpu_init_detectedx, sysinfo);

	ite_conf_clkin(CLKIN_DEV, ITE_UART_CLK_PREDIVIDE_24);
	ite_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();

	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);

#if 0
	dump_pci_device(PCI_DEV(0, 0x18, 0));
#endif

	setup_coherent_ht_domain();
	needs_reset = optimize_link_coherent_ht();

	wait_all_core0_started();
#if CONFIG_LOGICAL_CPUS
	/* It is said that we should start core1 after all core0 launched. */
	start_other_cores();
	wait_all_other_cores_started(bsp_apicid);
#endif

	ht_setup_chains_x(sysinfo);
	needs_reset |= ck804_early_setup_x();
	if (needs_reset) {
		printk(BIOS_INFO, "ht reset -\n");
		soft_reset();
	}

	allow_all_aps_stop(bsp_apicid);

	sysinfo->nodes = get_nodes();
	/* It's the time to set ctrl now. */
	fill_mem_ctrl(sysinfo->nodes, sysinfo->ctrl, spd_addr);

	enable_smbus();

#if 0
	dump_spd_registers(&ctrl[0]);
	dump_smbus_registers();
#endif

	sdram_initialize(sysinfo->nodes, sysinfo->ctrl, sysinfo);

#if 0
	print_pci_devices();
	dump_pci_devices();
#endif

	post_cache_as_ram();
}
