
DUT=nRF52840

DUTID=683887517


build:
	make -C device/$(DUT) DUT=1 build OBJECT_DIRECTORY=_build-dut

clean:
	make -C device/$(DUT) clean OBJECT_DIRECTORY=_build-dut

flash:
	make -C device/$(DUT) flash OBJECT_DIRECTORY=_build-dut DEVKITID=$(DUTID)


