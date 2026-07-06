/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_MODULE_H
#define _MACH_LKL_LINUX_MODULE_H

#include "../../../../../include/linux/module.h"

/*
 * Built-in MODULE_VERSION emits a struct into "__modver", which lacks
 * a Mach-O segment. The section must match the __start___modver /
 * __stop___modver markers in arch/lkl/kernel/vmlinux-mach-o.lds.S.
 */
#if defined(MODULE) || !defined(CONFIG_SYSFS)
/* original definitions are fine */
#else
#undef MODULE_VERSION
#define MODULE_VERSION(_version)					\
	MODULE_INFO(version, _version);					\
	static struct module_version_attribute __modver_attr		\
		__used __section("__DATA,__modver")			\
		__aligned(__alignof__(struct module_version_attribute)) \
		= {							\
			.mattr	= {					\
				.attr	= {				\
					.name	= "version",		\
					.mode	= S_IRUGO,		\
				},					\
				.show	= __modver_version_show,	\
			},						\
			.module_name	= KBUILD_MODNAME,		\
			.version	= _version,			\
		}
#endif

#endif /* _MACH_LKL_LINUX_MODULE_H */
