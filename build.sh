#!/bin/bash

clean () {
    rm -rf build/*
}

build () {
    make
    if [[ $? == 0 ]]; then
        echo "Creating grub config..."
        mkdir -p ./build/iso/boot/grub
        cp ./build/kernel.bin ./build/iso/boot
        cp ./iso/boot/grub/grub.cfg ./build/iso/boot/grub
        grub-mkrescue --output=./Simple-OS.iso ./build/iso
    fi
}

arg=$1
if [[ $# == 1 && "$arg" = "clean" ]]; then
    clean
elif [[ $# == 1 && "$arg" = "run" ]]; then
    if [[ ! -f Simple-OS.iso ]]; then
        echo "Image not exist"
        echo "Start building..."
        build
    fi

    echo "Starting OS..."
    qemu-system-x86_64 Simple-OS.iso
elif [[ $# == 0 ]] ; then
    build
else 
    echo "Unexcepted build command: " $1
fi