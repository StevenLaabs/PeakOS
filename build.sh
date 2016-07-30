cd kernel
make
cd ../
mkdir -p build/isofiles/boot/grub
mv kernel/peakos.kernel build
cp build/peakos.kernel build/isofiles/boot/peakos.kernel
cp kernel/grub.cfg build/isofiles/boot/grub
grub-mkrescue -o build/peakos.iso build/isofiles 2> /dev/null
rm -r build/isofiles
