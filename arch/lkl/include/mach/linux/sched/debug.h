/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_SCHED_DEBUG_H
#define _MACH_LKL_LINUX_SCHED_DEBUG_H

#include "../../../../../../include/linux/sched/debug.h"

#undef __sched
#define __sched __section("__TEXT,.sched.text,regular,pure_instructions")

#endif /* _MACH_LKL_LINUX_SCHED_DEBUG_H */
