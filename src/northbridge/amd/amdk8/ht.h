#ifndef AMDK8_HT_H
#define AMDK8_HT_H

#include "amdk8.h"

#define enable_bsp_routing()	enable_routing(0)

#define NODE_HT(x) PCI_DEV(0,24+x,0)
#define NODE_MP(x) PCI_DEV(0,24+x,1)
#define NODE_MC(x) PCI_DEV(0,24+x,3)

#define DEFAULT 0x00010101	/* default row entry */


#ifndef CROSS_BAR_47_56
	#define CROSS_BAR_47_56 0
#endif

#ifndef TRY_HIGH_FIRST
	#define TRY_HIGH_FIRST 0
#endif

#ifndef K8_HT_CHECK_PENDING_LINK
	#if CONFIG_MAX_PHYSICAL_CPUS >= 4
		#define K8_HT_CHECK_PENDING_LINK 1
	#else
		#define K8_HT_CHECK_PENDING_LINK 0
	#endif
#endif

#ifndef CONFIG_MAX_PHYSICAL_CPUS_4_BUT_MORE_INSTALLED
	#define CONFIG_MAX_PHYSICAL_CPUS_4_BUT_MORE_INSTALLED 0
#endif

// Do we need allocate MMIO? Current We direct last 64M to sblink only, We can not lose access to last 4M range to ROM
#ifndef K8_ALLOCATE_MMIO_RANGE
	#define K8_ALLOCATE_MMIO_RANGE 0
#endif

int set_ht_link_buffer_count(uint8_t node, uint8_t linkn, uint8_t linkt, unsigned val);
int set_ht_link_buffer_counts_chain(uint8_t ht_c_num, unsigned vendorid,  unsigned val);

#if CONFIG_RAMINIT_SYSINFO
void setup_coherent_ht_domain(void);
void ht_setup_chains_x(struct sys_info *sysinfo);
#else
int setup_coherent_ht_domain(void);
int ht_setup_chains_x(void);
#endif

int optimize_link_coherent_ht(void);
int optimize_link_incoherent_ht(struct sys_info *sysinfo);

unsigned get_sbdn(unsigned int);

#endif
