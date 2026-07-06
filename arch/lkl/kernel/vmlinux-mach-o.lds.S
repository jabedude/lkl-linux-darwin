/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Mach-O replacement for the vmlinux linker script.
 *
 * Apple's ld64 has no linker-script support, so this file is
 * *assembled* into an object (vmlinux-mach-o.o) that is placed first
 * on the final ld -r command line. Mach-O orders sections within a
 * segment by first occurrence in link order, so declaring every
 * order-sensitive section here, in the right sequence, both fixes the
 * relative order of the real content (contributed by later objects)
 * and plants the boundary labels at the start of each merged section.
 *
 * Section names are limited to 16 characters on Mach-O, hence the
 * shortened names; they must match the names used by the wrapper
 * headers in arch/lkl/include/mach/ and kernel/sched/sched.h.
 *
 * Kept free of `;` statement separators: the arm64 Mach-O assembler
 * treats `;` as a comment character. Only assembler macros and cpp
 * conditionals are used here.
 */

#include <asm/thread_info.h>

/* global label in the current section */
.macro lab sym:req
	.globl _\sym
_\sym:
.endm

/* declare a __DATA section, 8-byte aligned, with a boundary label */
.macro marker sect:req, sym:req
	.section __DATA,\sect
	.p2align 3
	lab \sym
.endm

/* declare a __DATA section without a label (ordering only) */
.macro secdecl sect:req
	.section __DATA,\sect
	.p2align 3
.endm

/* ------------------------------------------------------------------ */
/* initcalls: main.c iterates __initcall_start .. __initcall0_start   */
/* (early), then __initcallN_start .. __initcallN+1_start per level,  */
/* ending at __initcall_end. The Ns levels merge into level N's       */
/* region, matching KEEP(*(.initcallN.init .initcallNs.init)) in the  */
/* ELF script.                                                        */
/* ------------------------------------------------------------------ */

	marker .initcallearly, __initcall_start
	marker .initcall0, __initcall0_start
	marker .initcall1, __initcall1_start
	secdecl .initcall1s
	marker .initcall2, __initcall2_start
	secdecl .initcall2s
	marker .initcall3, __initcall3_start
	secdecl .initcall3s
	marker .initcall4, __initcall4_start
	secdecl .initcall4s
	marker .initcall5, __initcall5_start
	secdecl .initcall5s
	marker .initcallrootfs, __initcallrootfs_start
	marker .initcall6, __initcall6_start
	secdecl .initcall6s
	marker .initcall7, __initcall7_start
	secdecl .initcall7s
	marker .initcall_end, __initcall_end

/* console initcalls (printk/console.c) */
	marker .con_initcall, __con_initcall_start
	marker .con_initcallE, __con_initcall_end

/* boot command line __setup/early_param table (init/main.c) */
	marker .init.setup, __setup_start
	marker .init.setupE, __setup_end

/* built-in module parameters (kernel/params.c) */
	marker __param, __start___param
	marker __paramE, __stop___param

/* built-in MODULE_VERSION attributes (kernel/params.c, CONFIG_SYSFS) */
	marker __modver, __start___modver
	marker __modverE, __stop___modver

/* ------------------------------------------------------------------ */
/* struct sched_class instances, highest priority first; the          */
/* scheduler walks them with pointer arithmetic so they must be       */
/* contiguous and in this exact order (see SCHED_DATA in              */
/* asm-generic/vmlinux.lds.h and DEFINE_SCHED_CLASS in                */
/* kernel/sched/sched.h).                                             */
/* ------------------------------------------------------------------ */

	marker .sched.hi, __sched_class_highest
#ifdef CONFIG_SMP
	secdecl .sched.stop
#endif
	secdecl .sched.dl
	secdecl .sched.rt
	secdecl .sched.fair
#ifdef CONFIG_SCHED_CLASS_EXT
	secdecl .sched.ext
#endif
	secdecl .sched.idle
	marker .sched.lo, __sched_class_lowest

/* ------------------------------------------------------------------ */
/* Boundary symbols generic code links against. vmlinux is linked     */
/* incrementally (ld -r), so these never get meaningful final         */
/* addresses; they are referenced for informational purposes only     */
/* (boot-time size prints, core_kernel_text() etc). Zero-size labels. */
/* ------------------------------------------------------------------ */

	.section __TEXT,.lkl.text.mark
	lab _stext
	lab _text
	lab _sinittext
	lab _einittext
	lab __sched_text_start
	lab __sched_text_end
	lab __cpuidle_text_start
	lab __cpuidle_text_end
	lab __noinstr_text_start
	lab __noinstr_text_end
	lab __softirqentry_text_start
	lab __softirqentry_text_end
	lab __irqentry_text_start
	lab __irqentry_text_end
	lab __entry_text_start
	lab __entry_text_end
	lab _etext

/* ------------------------------------------------------------------ */
/* Initial task stack. The ELF script overlays init_thread_union /    */
/* init_stack onto the .data..init_thread_info input section and      */
/* reserves THREAD_SIZE bytes (INIT_TASK_DATA). Mach-O equivalent:    */
/* plant the labels at the head of the section that receives the      */
/* C-initialized init_thread_info (see __init_thread_info in          */
/* linux/init_task.h), then back the rest of the stack area with a    */
/* THREAD_SIZE pad section that follows it in the segment.            */
/* ------------------------------------------------------------------ */

	.section __DATA,.data..init_thr
	.p2align 4
	lab init_thread_union
	lab init_stack

	.section __DATA,.init_stack.pad
	.p2align 4
	.space THREAD_SIZE

	.section __DATA,.lkl.data.mark
	.p2align 3
	lab __init_begin
	lab __init_end
	lab _sdata
	lab __start_rodata
	lab __end_rodata
	lab _edata
	lab __start___ex_table
	lab __stop___ex_table
	lab __start_notes
	lab __stop_notes
	lab __bss_start
	lab __bss_stop
	lab _end
