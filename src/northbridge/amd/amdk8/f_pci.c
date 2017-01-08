#include "f_pci.h"

uint32_t pci_read_config32_index_wait(pci_devfn_t dev,
		uint32_t index_reg, uint32_t index)
{
	uint32_t dword;

	index &= ~(1<<30);
	pci_write_config32(dev, index_reg, index);

	do {
		dword = pci_read_config32(dev, index_reg);
	} while (!(dword & (1<<31)));

	dword = pci_read_config32(dev, index_reg+0x4);

	return dword;
}

void pci_write_config32_index_wait(pci_devfn_t dev, uint32_t index_reg,
		uint32_t index, uint32_t data)
{
	uint32_t dword;

	pci_write_config32(dev, index_reg + 0x4, data);

	index |= (1<<30);
	pci_write_config32(dev, index_reg, index);
	do {
		dword = pci_read_config32(dev, index_reg);
	} while (!(dword & (1<<31)));
}
