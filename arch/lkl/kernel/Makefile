extra-y := vmlinux.lds

obj-y = setup.o threads.o irq.o time.o syscalls.o misc.o console.o \
	syscalls_32.o cpu.o

ifeq ($(OUTPUT_FORMAT),mach-o-x86-64)
extra-y += mach-o-linker.o vmlinux-mach-o.lds vmlinux-mach-o.o
endif

# arm64 Mach-O as treats ';' as a comment char, not a statement
# separator like x86 did, so split statements onto real lines first
$(obj)/vmlinux-mach-o.o: $(src)/vmlinux-mach-o.lds FORCE
	$(Q)tr ';' '\n' < $< | $(AS) -c -o $@ -
