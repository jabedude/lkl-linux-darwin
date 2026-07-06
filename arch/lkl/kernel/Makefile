extra-y := vmlinux.lds
extra-y += vmlinux-fuzzing-postlink.lds

KASAN_SANITIZE_init.o := n
KASAN_SANITIZE_stacktrace.o := n

obj-y = setup.o threads.o irq.o time.o syscalls.o misc.o console.o \
	syscalls_32.o cpu.o init.o stacktrace.o

ifneq (,$(findstring mach-o,$(CONFIG_OUTPUT_FORMAT)))
extra-y += vmlinux-mach-o.lds vmlinux-mach-o.o
obj-y += mach-o-fixups.o

# Apple's ld64 has no linker-script support: assemble the ordering /
# boundary-symbol object that stands in for the linker script (see
# vmlinux-mach-o.lds.S; the .lds is its cpp-processed form).
quiet_cmd_as_macho_lds = AS      $@
      cmd_as_macho_lds = $(CC) -x assembler -c -o $@ $<

$(obj)/vmlinux-mach-o.o: $(obj)/vmlinux-mach-o.lds FORCE
	$(call if_changed,as_macho_lds)
endif
