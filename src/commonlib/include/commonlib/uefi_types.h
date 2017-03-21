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

#ifndef __UEFI_TYPES_H__
#define __UEFI_TYPES_H__

#include <stdint.h>

#define SIGNATURE_16(A, B)		((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)	(SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))

#define EFI_TE_IMAGE_HEADER_SIGNATURE	SIGNATURE_16('V', 'Z')
#define EFI_TE_IMAGE_DIRECTORY_ENTRY_BASERELOC 0
#define EFI_FVH_SIGNATURE		SIGNATURE_32 ('_', 'F', 'V', 'H')

#define EFI_IMAGE_REL_BASED_ABSOLUTE		0
#define EFI_IMAGE_REL_BASED_HIGHLOW		3
#define EFI_SECTION_TE				0x12
#define EFI_SECTION_RAW				0x19
#define FFS_ATTRIB_LARGE_FILE			0x01
#define EFI_FV_FILETYPE_FFS_MAX			0xff
#define EFI_FV_FILETYPE_FFS_PAD			0xf0

#define EFI_FIRMWARE_FILE_SYSTEM2_GUID \
{ 0x8c8ce578, 0x8a3d, 0x4f1c, { 0x99, 0x35, 0x89, 0x61, 0x85, 0xc3, 0x2d, 0xd3 } }

struct EFI_GUID {
	uint32_t Data1;
	uint16_t Data2;
	uint16_t Data3;
	uint8_t Data4[8];
} __attribute__((packed));

struct EFI_IMAGE_DATA_DIRECTORY {
	uint32_t VirtualAddress;
	uint32_t Size;
} __attribute__((packed));

struct EFI_IMAGE_BASE_RELOCATION {
	uint32_t VirtualAddress;
	uint32_t SizeOfBlock;
} __attribute__((packed));

struct EFI_TE_IMAGE_HEADER {
	uint16_t Signature;
	uint16_t Machine;
	uint8_t NumberOfSections;
	uint8_t Subsystem;
	uint16_t StrippedSize;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint64_t ImageBase;
	struct EFI_IMAGE_DATA_DIRECTORY DataDirectory[2];
} __attribute__((packed));


struct EFI_COMMON_SECTION_HEADER {
	uint8_t Size[3];
	uint8_t Type;
} __attribute__((packed));

struct EFI_COMMON_SECTION_HEADER2 {
	uint8_t Size[3];
	uint8_t Type;
	uint32_t ExtendedSize;
} __attribute__((packed));

struct EFI_FFS_FILE_HEADER {
	struct EFI_GUID Name;
	uint16_t IntegrityCheck;
	uint8_t Type;
	uint8_t Attributes;
	uint8_t Size[3];
	uint8_t State;
} __attribute__((packed));

struct EFI_FFS_FILE_HEADER2 {
	struct EFI_GUID Name;
	uint8_t IntegrityCheck;
	uint8_t Type;
	uint8_t Attributes;
	uint8_t Size[3];
	uint8_t State;
	uint32_t ExtendedSize; /* 64-bit in newer EFI headers */
} __attribute__((packed));

static inline int IS_FFS_FILE2(const struct  EFI_FFS_FILE_HEADER *ffsfh)
{
	return !!(ffsfh->Attributes & FFS_ATTRIB_LARGE_FILE);
}

struct EFI_FIRMWARE_VOLUME_HEADER {
	uint8_t ZeroVector[16];
	struct EFI_GUID FileSystemGuid;
	uint64_t FvLength;
	uint32_t Signature;
	uint32_t Attributes;
	uint16_t HeaderLength;
	uint16_t Checksum;
	uint16_t ExtHeaderOffset;
	uint8_t Reserved[1];
	uint8_t Revision;
	uint32_t BlockMap[1];
} __attribute__((packed));

struct EFI_FIRMWARE_VOLUME_EXT_HEADER {
	struct EFI_GUID FvName;
	uint32_t ExtHeaderSize;
} __attribute__((packed));

#endif	/* __UEFI_TYPES_H__*/
