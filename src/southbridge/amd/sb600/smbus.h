/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
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

#ifndef SB600_SMBUS_H
#define SB600_SMBUS_H

#include <stdint.h>
#include <arch/io.h>

#define SMBHSTSTAT 0x0
#define SMBSLVSTAT 0x1
#define SMBHSTCTRL 0x2
#define SMBHSTCMD  0x3
#define SMBHSTADDR 0x4
#define SMBHSTDAT0 0x5
#define SMBHSTDAT1 0x6
#define SMBHSTBLKDAT 0x7

#define SMBSLVCTRL 0x8
#define SMBSLVCMD_SHADOW 0x9
#define SMBSLVEVT 0xa
#define SMBSLVDAT 0xc

#define AX_INDXC  0
#define AX_INDXP  1
#define AXCFG     2
#define ABCFG     3

#define AB_INDX   0xCD8
#define AB_DATA   (AB_INDX+4)

/* Between 1-10 seconds, We should never timeout normally
 * Longer than this is just painful when a timeout condition occurs.
 */
#define SMBUS_TIMEOUT (100*1000*10)

static void alink_ab_indx(u32 reg_space, u32 reg_addr, u32 mask, u32 val)
{
	u32 tmp;

	outl((reg_space & 0x3) << 30 | reg_addr, AB_INDX);
	tmp = inl(AB_DATA);

	tmp &= ~mask;
	tmp |= val;

	/* printk(BIOS_DEBUG, "about write %x, index=%x", tmp, (reg_space&0x3)<<30 | reg_addr); */
	outl((reg_space & 0x3) << 30 | reg_addr, AB_INDX);	/* probably we don't have to do it again. */
	outl(tmp, AB_DATA);
}

/* space = 0: AX_INDXC, AX_DATAC
*   space = 1: AX_INDXP, AX_DATAP
 */
static void alink_ax_indx(u32 space /*c or p? */ , u32 axindc,
			  u32 mask, u32 val)
{
	u32 tmp;

	/* read axindc to tmp */
	outl(space << 30 | space << 3 | 0x30, AB_INDX);
	outl(axindc, AB_DATA);
	outl(space << 30 | space << 3 | 0x34, AB_INDX);
	tmp = inl(AB_DATA);

	tmp &= ~mask;
	tmp |= val;

	/* write tmp */
	outl(space << 30 | space << 3 | 0x30, AB_INDX);
	outl(axindc, AB_DATA);
	outl(space << 30 | space << 3 | 0x34, AB_INDX);
	outl(tmp, AB_DATA);
}

#define abcfg_reg(reg, mask, val)	\
	alink_ab_indx((ABCFG), (reg), (mask), (val))
#define axcfg_reg(reg, mask, val)	\
	alink_ab_indx((AXCFG), (reg), (mask), (val))
#define axindxc_reg(reg, mask, val)	\
	alink_ax_indx(0, (reg), (mask), (val))
#define axindxp_reg(reg, mask, val)	\
	alink_ax_indx(1, (reg), (mask), (val))

int do_smbus_recv_byte(u32 smbus_io_base, u32 device);
int do_smbus_send_byte(u32 smbus_io_base, u32 device, u8 val);
int do_smbus_read_byte(u32 smbus_io_base, u32 device, u32 address);
int do_smbus_write_byte(u32 smbus_io_base, u32 device, u32 address, u8 val);

#endif
