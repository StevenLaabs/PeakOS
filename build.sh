cd kernel
make
cd ../
mkdir -p build/obj
mv kernel/*.o build/obj
mkdir -p build/isofiles/boot/grub
mv kernel/kernel.bin build
cp build/kernel.bin build/isofiles/boot/kernel.bin
cp kernel/grub.cfg build/isofiles/boot/grub
grub-mkrescue -o build/hobby-os.iso build/isofiles 2> /dev/null
rm -r build/isofiles
