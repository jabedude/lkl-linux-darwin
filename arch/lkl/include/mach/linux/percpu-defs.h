/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_PERCPU_DEFS_H
#define _MACH_LKL_LINUX_PERCPU_DEFS_H

#include "../../../../../include/linux/percpu-defs.h"

/*
 * !SMP percpu variables live in plain ".data(..suffix)" sections,
 * which lack Mach-O segments. Collapse all percpu variants into one
 * data section; with one CPU their relative layout is irrelevant.
 */
#undef __PCPU_ATTRS
#define __PCPU_ATTRS(sec)						\
	__percpu __section("__DATA,.data..percpu")			\
	PER_CPU_ATTRIBUTES

#endif /* _MACH_LKL_LINUX_PERCPU_DEFS_H */
