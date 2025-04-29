#!/bin/bash
set -ex
DISK=/tmp/disk.img
FLAGS=(
	-enable-kvm
	-cpu host
	-serial stdio
	-drive file=$DISK,format=raw,if=none,id=sda
	-display vnc=:11
	-device qemu-xhci
	-device usb-kbd
	-device virtio-scsi-pci
	-device scsi-hd,drive=sda
	$@
)
rm -f $DISK
fallocate -l 256M $DISK
parted -s $DISK mklabel gpt
parted -s $DISK mkpart boot 2048s 100%
parted -s $DISK set 1 esp on
LOOP=$(losetup -f -P --show $DISK)
mkfs.vfat -F32 ${LOOP}p1
mkdir -p /tmp/disk
mount -t vfat ${LOOP}p1 /tmp/disk
mkdir -p /tmp/disk/efi/boot/
cp build/efifetch.efi /tmp/disk/
CARCH="$(uname -m)"
case "${ARCH:-${CARCH}}" in
	aarch64|armv8|armv8l|armv8a)
		FLAGS+=(
			-machine virt
			-device virtio-gpu
			-bios /usr/share/edk2/aarch64/QEMU_EFI.fd
		)
		QEMU_ARCH=aarch64
		cp /usr/share/edk2-shell/aarch64/Shell_Full.efi /tmp/disk/efi/boot/bootaa64.efi
	;;
	x86_64|x64|amd64)
		FLAGS+=(
			-machine q35
			-bios /usr/share/edk2/x64/OVMF.4m.fd
		)
		QEMU_ARCH=x86_64
		cp /usr/share/edk2-shell/x64/Shell_Full.efi /tmp/disk/efi/boot/bootx64.efi
	;;
	i386|i486|i586|i686|x86|ia32)
		FLAGS+=(
			-machine q35
			-bios /usr/share/edk2/ia32/OVMF.4m.fd
		)
		QEMU_ARCH=i386
		cp /usr/share/edk2-shell/ia32/Shell_Full.efi /tmp/disk/efi/boot/bootia32.efi
	;;
	*)exit 1;;
esac
cat <<EOF > /tmp/disk/startup.nsh
ifconfig -s eth0 dhcp
stall 300000
fs0:
efifetch
EOF
umount /tmp/disk
losetup -d $LOOP
exec qemu-system-${QEMU_ARCH} ${FLAGS[@]}
