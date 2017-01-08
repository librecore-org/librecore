/*
 * This file is part of the coreboot project.
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

#ifndef INIT_CPUS_H
#define INIT_CPUS_H

#include <stdint.h>
#include <northbridge/amd/amdk8/amdk8.h>

#define LAPIC_MSG_REG 0x380

typedef void (*process_ap_t) (u32 apicid, void *gp);

//core_range = 0 : all cores
//core range = 1 : core 0 only
//core range = 2 : cores other than core0

/*
static void for_each_ap(u32 bsp_apicid, u32 core_range, process_ap_t process_ap,
			void *gp);
static inline int lapic_remote_read(int apicid, int reg, u32 *pvalue);

#if CONFIG_SET_FIDVID
static void init_fidvid_ap(u32 bsp_apicid, u32 apicid);
#endif

static inline __attribute__ ((always_inline))
void print_apicid_nodeid_coreid(u32 apicid, struct node_core_id id,
				const char *str);
static void wait_ap_started(u32 ap_apicid, void *gp);
static void enable_apic_ext_id(u32 node);
static void STOP_CAR_AND_CPU(void);
static u32 is_core0_started(u32 nodeid);
*/

#if CONFIG_RAMINIT_SYSINFO
u32 init_cpus(u32 cpu_init_detectedx, struct sys_info *sysinfo);
#else
u32 init_cpus(u32 cpu_init_detectedx);
#endif

int lapic_remote_read(int apicid, int reg, u32 *pvalue);
u32 wait_cpu_state(u32 apicid, u32 state);
void init_fidvid_ap(unsigned bsp_apicid, unsigned apicid);
uint8_t set_apicid_cpuid_lo(void);
void wait_all_aps_started(u32 bsp_apicid);
void wait_all_other_cores_started(u32 bsp_apicid);
void allow_all_aps_stop(u32 bsp_apicid);
void wait_all_core0_started(void);
void for_each_ap(u32 bsp_apicid, u32 core_range, process_ap_t process_ap,
		void *gp);
void enable_fid_change(void);
void init_fidvid_bsp(unsigned bsp_apicid);

void post_cache_as_ram(void);

#endif
