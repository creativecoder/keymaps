# Default keymap
km ?= creativecoder

kyria: kyria-left

kyria-left:
	qmk flash -kb splitkb/kyria/rev1 -km $(km) -e MAKE_TARGET=dfu-split-left

kyria-right:
	qmk flash -kb splitkb/kyria/rev1 -km $(km) -e MAKE_TARGET=dfu-split-right

doio:
	qmk flash -kb doio/kb16/rev2 -km $(km)

# Requires sudo
.PHONY: keyd
keyd:
	cp keyd/* /etc/keyd/
	/usr/local/bin/keyd reload
