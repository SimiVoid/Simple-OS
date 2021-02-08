GPPPARAMS = -m32 -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386 --allow-multiple-definition

objects = loader.o kernel.o io.o vga.o lowlevel.o string.o sys.o
%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<
	
kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	rm -rf $(objects)

install: kernel.bin
	sudo cp $< /boot/kernel.bin
	
Simple-OS.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout-0' 				>> iso/boot/grub/grub.cfg
	echo 'set default-0' 				>> iso/boot/grub/grub.cfg
	echo 'menuentry "Simple OS"{' 		>> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' 						>> iso/boot/grub/grub.cfg
	echo '}' 							>> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	rm -f kernel.bin

clean:
	rm -rf $(objects)
