/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_INTERRUPT_H
#define _MACH_LKL_LINUX_INTERRUPT_H

#include "../../../../../include/linux/interrupt.h"

/* ".softirqentry.text" exceeds Mach-O's 16-char section name limit */
#undef __softirq_entry
#define __softirq_entry \
	__section("__TEXT,.sirq.text,regular,pure_instructions")

#endif /* _MACH_LKL_LINUX_INTERRUPT_H */
