subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY16_KB) += f16kb

ifeq ($(CONFIG_CPU_AMD_AGESA),y)

subdirs-y += common

classes-y += libagesa
libagesa-y =
libagesa-generic-ccopts += -D__LIBAGESA__

ifeq ($(CONFIG_ARCH_ROMSTAGE_X86_32),y)
$(eval $(call create_class_compiler,libagesa,x86_32))
else
$(eval $(call create_class_compiler,libagesa,x86_64))
endif

endif
