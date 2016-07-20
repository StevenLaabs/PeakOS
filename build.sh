cd kernel
make
cd ../
mkdir -p build/isofiles/boot/grub
mv kernel/hobby-os.kernel build
cp build/hobby-os.kernel build/isofiles/boot/hobby-os.kernel
cp kernel/grub.cfg build/isofiles/boot/grub
grub-mkrescue -o build/hobby-os.iso build/isofiles 2> /dev/null
rm -r build/isofiles
