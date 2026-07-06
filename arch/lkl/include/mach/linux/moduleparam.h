/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_MODULEPARAM_H
#define _MACH_LKL_LINUX_MODULEPARAM_H

#include "../../../../../include/linux/moduleparam.h"

/*
 * "__param" and ".modinfo" lack Mach-O segments. __param must match
 * the section declared in arch/lkl/kernel/vmlinux-mach-o.lds.S so the
 * __start___param/__stop___param boundaries hold.
 */

#undef __module_param_call
#define __module_param_call(prefix, name, ops, arg, perm, level, flags)	\
	/* Default value instead of permissions? */			\
	static const char __param_str_##name[] = prefix #name;		\
	static struct kernel_param __moduleparam_const __param_##name	\
	__used __section("__DATA,__param")				\
	__aligned(__alignof__(struct kernel_param))			\
	= { __param_str_##name, THIS_MODULE, ops,			\
	    VERIFY_OCTAL_PERMISSIONS(perm), level, flags, { arg } }

#undef __MODULE_INFO
#define __MODULE_INFO(tag, name, info)					  \
	static const char __UNIQUE_ID(name)[]				  \
		__used __section("__DATA,.modinfo") __aligned(1)	  \
		= __MODULE_INFO_PREFIX __stringify(tag) "=" info

#endif /* _MACH_LKL_LINUX_MODULEPARAM_H */
