/*
 * This file is part of the coreboot project.
 *
 * Copyright 2017 Adurb Akhbar <aakhbar@mail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _FSP_INFO_HEADER_H_
#define _FSP_INFO_HEADER_H_

#include <stdint.h>

#define FSP_SIG		0x48505346	/* 'FSPH' */

#define FSP_INFO_HEADER_GUID					\
{								\
	0x912740BE, 0x2284, 0x4734,				\
	{0xB9, 0x71, 0x84, 0xB0, 0x27, 0x35, 0x3F, 0x0C}	\
}

struct FSP_INFO_HEADER {
	uint32_t Signature;
	uint32_t HeaderLength;
	uint8_t Reserved1[3];
	uint8_t HeaderRevision;
	uint32_t ImageRevision;
	char ImageId[8];
	uint32_t ImageSize;
	uint32_t ImageBase;
	uint32_t ImageAttribute;
	uint32_t CfgRegionOffset;
	uint32_t CfgRegionSize;
	uint32_t ApiEntryNum;
	uint32_t TempRamInitEntryOffset;
	uint32_t FspInitEntryOffset;
	uint32_t NotifyPhaseEntryOffset;
	uint32_t FspMemoryInitEntryOffset;
	uint32_t TempRamExitEntryOffset;
	uint32_t FspSiliconInitEntryOffset;
} __attribute__ ((packed));

struct FSP_EXTENTED_HEADER {
	uint32_t Signature;
	uint32_t HeaderLength;
	uint8_t Revision;
	uint8_t Reserved;
	char OemId[6];
	uint32_t OemRevision;
} __attribute__ ((packed));

#endif
