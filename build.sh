cd kernel
make
cd ../
mkdir -p build/isofiles/boot/grub
mv kernel/peakos.kernel build
cp build/peakos.kernel build/isofiles/boot/peakos.kernel
cat > build/isofiles/boot/grub/grub.cfg << EOF
set timeout=0
set default=0

menuentry "PeakOS" {
	multiboot /boot/peakos.kernel
	boot
}
EOF
grub-mkrescue -o build/peakos.iso build/isofiles 2> /dev/null
