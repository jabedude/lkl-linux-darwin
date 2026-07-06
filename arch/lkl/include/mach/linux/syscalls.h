/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MACH_LKL_LINUX_SYSCALLS_H
#define _MACH_LKL_LINUX_SYSCALLS_H

#include "../../../../../include/linux/syscalls.h"

/*
 * Mach-O clang does not support __attribute__((alias)); emit sys##name
 * as a real trampoline into __se_sys##name instead of an alias of it.
 * Everything else matches the original __SYSCALL_DEFINEx.
 */

/* cast a typed syscall arg to the long register representation */
#define __SC_MACH_LCAST(t, a)	(long)(a)

#undef __SYSCALL_DEFINEx
#define __SYSCALL_DEFINEx(x, name, ...)					\
	static inline long __do_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));\
	asmlinkage long __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));	\
	asmlinkage long __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))	\
	{								\
		long ret = __do_sys##name(__MAP(x,__SC_CAST,__VA_ARGS__));\
		__MAP(x,__SC_TEST,__VA_ARGS__);				\
		__PROTECT(x, ret,__MAP(x,__SC_ARGS,__VA_ARGS__));	\
		return ret;						\
	}								\
	asmlinkage long sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));	\
	asmlinkage long sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))	\
	{								\
		return __se_sys##name(__MAP(x,__SC_MACH_LCAST,__VA_ARGS__));\
	}								\
	static inline long __do_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

#endif /* _MACH_LKL_LINUX_SYSCALLS_H */
