#define __SIMPLE_DEVICE__

#include <arch/io.h>
#include <reset.h>
#include <device/pci_ids.h>

extern void set_bios_reset(void);
extern unsigned node_link_to_bus(unsigned node, unsigned link);
extern unsigned get_sblk(void);

void hard_reset(void)
{
	pci_devfn_t dev;
	unsigned bus;
	unsigned node = 0;
	unsigned link = get_sblk();

	/* Find the device.
	 * There can only be one 8111 on a hypertransport chain/bus.
	 */
	bus = node_link_to_bus(node, link);
	dev = pci_locate_device_on_bus(
		PCI_ID(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8111_ISA),
		bus);

	/* Reset */
	set_bios_reset();
	pci_write_config8(dev, 0x47, 1);
}
