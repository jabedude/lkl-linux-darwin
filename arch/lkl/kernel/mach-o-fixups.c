// SPDX-License-Identifier: GPL-2.0
/*
 * Mach-O section-ordering insurance.
 *
 * Section order in a Mach-O incremental link follows first occurrence
 * in link order; arch/lkl/kernel/vmlinux-mach-o.lds.S (linked first)
 * declares every initcall level section in the right sequence. On the
 * 4.19 port an initcall level with no members ended up relocated
 * after later levels, corrupting the level boundaries that
 * init/main.c walks. Guarantee every level has at least one member.
 */
#include <linux/init.h>

static int __init lkl_macho_initcall_pad(void)
{
	return 0;
}

early_initcall(lkl_macho_initcall_pad);
pure_initcall(lkl_macho_initcall_pad);
core_initcall(lkl_macho_initcall_pad);
core_initcall_sync(lkl_macho_initcall_pad);
postcore_initcall(lkl_macho_initcall_pad);
postcore_initcall_sync(lkl_macho_initcall_pad);
arch_initcall(lkl_macho_initcall_pad);
arch_initcall_sync(lkl_macho_initcall_pad);
subsys_initcall(lkl_macho_initcall_pad);
subsys_initcall_sync(lkl_macho_initcall_pad);
fs_initcall(lkl_macho_initcall_pad);
fs_initcall_sync(lkl_macho_initcall_pad);
rootfs_initcall(lkl_macho_initcall_pad);
device_initcall(lkl_macho_initcall_pad);
device_initcall_sync(lkl_macho_initcall_pad);
late_initcall(lkl_macho_initcall_pad);
late_initcall_sync(lkl_macho_initcall_pad);
