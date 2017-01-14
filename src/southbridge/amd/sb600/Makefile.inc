ifeq ($(CONFIG_SOUTHBRIDGE_AMD_SB600),y)

romstage-y += smbus.c
romstage-$(CONFIG_USBDEBUG_IN_ROMSTAGE) += enable_usbdebug.c

ramstage-y += sb600.c
ramstage-y += usb.c
ramstage-y += lpc.c
ramstage-y += sm.c
ramstage-y += ide.c
ramstage-y += sata.c
ramstage-y += hda.c
ramstage-y += ac97.c
ramstage-y += pci.c
ramstage-y += reset.c
ramstage-$(CONFIG_USBDEBUG) += enable_usbdebug.c
ramstage-y += smbus.c

endif
