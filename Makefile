O ?= build
ARCH ?= $(shell $(CC) -dumpmachine | cut -d- -f1)
EDK2_PATH ?= edk2
EDK2_TARGET ?= RELEASE
EDK2_TOOLCHAIN ?= GCC5
EDK_TOOLS_PATH ?= $(EDK2_PATH)/BaseTools
PACKAGES_PATH ?= $(EDK2_PATH)/edk2:$(PWD)
X_CCFLAGS = \
	-g -Iefifetch/include \
	-nostdlib -nodefaultlibs -nolibc -nostdinc \
	-O3 -Wall -Wextra -Werror -Werror=stack-usage=4096 \
	-fpic -ffreestanding -fstack-protector -fno-stack-check \
	-fshort-wchar -fno-builtin -fno-common -fno-strict-aliasing \
	-fdata-sections -ffunction-sections -mgeneral-regs-only \
	-fno-jump-tables \
	-mstack-protector-guard=global \
	-Wno-sign-compare -Wno-unused-parameter
X_LDFLAGS = \
	-g -shared -Bsymbolic --no-undefined \
	-Tefifetch/entry/efi-$(ARCH).lds
X_LIBS =
X_COPYFLAGS = \
	-j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym \
	-j .rel -j .rela -j .rel.* -j .rela.* -j .reloc \
	--subsystem=10
ifeq ($(ARCH),x86_64)
	X_COPYFLAGS += --target pei-x86-64
	X_CCFLAGS += -mno-red-zone -maccumulate-outgoing-args -mcmodel=small
	EDK2_ARCH = X64
else ifeq ($(ARCH),aarch64)
	X_COPYFLAGS += --target pei-aarch64-little
	X_CCFLAGS += -ffixed-x18 -mstrict-align -mcmodel=small
	EDK2_ARCH = AARCH64
else ifeq ($(ARCH),riscv64)
	X_COPYFLAGS += --target pei-riscv64-little
	EDK2_ARCH = RISCV64
else ifeq ($(ARCH),i386)
	X_COPYFLAGS += --target pei-i386
	X_CCFLAGS += -m32 -malign-double
	X_LDFLAGS += -m elf_i386 
	X_LIBS += $(shell $(CC) $(X_CCFLAGS) -print-libgcc-file-name)
	EDK2_ARCH = IA32
else
$(error Unsupported architecture: $(ARCH))
endif

include efifetch/objs.mk

all: $(O)/efifetch.efi

-include $(O)/*.deps
-include $(O)/*/*.deps

$(O)/%.c.o: efifetch/%.c
	@mkdir -p $(@D)
	$(CC) -MMD -MF $@.deps $(X_CCFLAGS) -c $< -o $@

$(O)/%.S.o: efifetch/%.S
	@mkdir -p $(@D)
	$(CC) -MMD -MF $@.deps -DASM $(X_CCFLAGS) -c $< -o $@

$(O)/efifetch.so: $(OBJS)
	@mkdir -p $(@D)
	$(LD) $(X_LDFLAGS) $^ $(X_LIBS) -o $@

$(O)/efifetch.efi: $(O)/efifetch.so
	@mkdir -p $(@D)
	objcopy $(X_COPYFLAGS) $^ $@
	strip $@

clean:
	find $(O) -type f -name '*.o' -delete
	find $(O) -type f -name '*.deps' -delete
	rm -f $(O)/efifetch.so
	rm -f $(O)/efifetch.efi

build-edk2:
	source $(EDK2_PATH)/edksetup.sh; \
	$(MAKE) -C $(EDK_TOOLS_PATH); \
	build \
		-a $(EDK2_ARCH) \
		-t $(EDK2_TOOLCHAIN) \
		-b $(EDK2_TARGET) \
		-p efifetch/efifetch.dsc

.PHONY: all clean build-edk2
