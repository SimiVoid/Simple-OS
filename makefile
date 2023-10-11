INC_DIR = ./include/
GPPPARAMS = -m32 -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fpermissive -I$(INC_DIR)
ASPARAMS = --32
LDPARAMS = -melf_i386 --allow-multiple-definition

objects = ./src/loader.o $(shell find -name "*.cpp" | sed "s/cpp/o /g")
build_objects = ./build/src/loader.o $(shell find -name "*.cpp" | sed "s+\./+./build/+g" | sed "s/cpp/o /g")

%.o: %.cpp
	@echo "Building ./$<"
	@mkdir -p ./build/$(shell dirname $<)
	@g++ $(GPPPARAMS) -o ./build/$@ -c $<

%.o: %.s
	@echo "Building ./$<"
	@mkdir -p ./build/$(shell dirname $<)
	@as $(ASPARAMS) -o ./build/$@ $<

kernel.bin: linker.ld $(objects)
	@echo "Linking liblaries..."
	@ld $(LDPARAMS) -T $< -o ./build/$@ $(build_objects)
