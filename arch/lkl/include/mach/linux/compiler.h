/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_COMPILER_H
#define _MACH_LKL_LINUX_COMPILER_H

#include "../../../../../include/linux/compiler.h"

/*
 * ".discard.addressable" is an ELF section name (and the section is
 * discarded by the ELF linker script anyway). Mach-O section
 * specifiers need a segment and a <=16 char section name. Keep the
 * "take the address" side effect, drop the section placement: nothing
 * discards it here, and without LTO/--gc-sections nothing needs it.
 */
#undef ___ADDRESSABLE
#define ___ADDRESSABLE(sym, __attrs)					\
	static void * __used						\
	__UNIQUE_ID(__PASTE(__addressable_, sym)) = (void *)(uintptr_t)&sym;

#endif /* _MACH_LKL_LINUX_COMPILER_H */
