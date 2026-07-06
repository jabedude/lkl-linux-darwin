/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_CACHE_H
#define _MACH_LKL_LINUX_CACHE_H

#include "../../../../../include/linux/cache.h"

#undef __ro_after_init
#define __ro_after_init __section("__DATA,.ro_after_init")

#undef __cacheline_aligned
#define __cacheline_aligned					\
	__attribute__((__aligned__(SMP_CACHE_BYTES),		\
		       __section__("__DATA,.data..cl")))

#endif /* _MACH_LKL_LINUX_CACHE_H */
