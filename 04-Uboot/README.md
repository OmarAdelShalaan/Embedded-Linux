# U-boot

U-Boot is **the most popular boot loader in** **linux** **based embedded devices**. It is released as open source under the GNU GPLv2 license. It supports a wide range of microprocessors like MIPS, ARM, PPC, Blackfin, AVR32 and x86.

## Setup U-boot

### Download U-Boot

```bash
git clone git@github.com:u-boot/u-boot.git
cd u-boot/
git checkout v2022.07
```

### Configure U-Boot Machine

In this section we will **configure** u-boot for several Machine

```bash
# In order to find the machine supported by U-Boot
ls configs/ | grep [your machine] 
# ls configs | grep vexpress*
```

#### Vexpress Cortex A9 (Qemu)

In **U-boot directory** Assign this value

```bash
# Set the Cross Compiler into the environment
# To be used by the u-boot
# Compiler out from Crosstool-NG
export CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm

# load the default configuration of ARM Vexpress Cortex A9
make vexpress_ca9x4_defconfig
```

#### Raspberry Pi

First we need to download the **compiler** for the architecture set for **RPI**

```bash
# update the package manager
sudo apt-get update

# the following compiler support 32 bit architecture
sudo apt-get install gcc-arm-linux-gnueabihf-

# in case of using architecture 64 Download the following compiler
sudo apt-get install gcc-aarch64-linux-gnu
```

##### Raspberry Pi 3

In **U-boot directory** Assign this value

```bash
# Set the Cross Compiler into the environment
# To be used by the u-boot
export CROSS_COMPILE=arm-linux-gnueabihf-
export ARCH=arm

# load the default configuration of rpi 3
make rpi_3_defconfig
```

##### Raspberry Pi 4

In **U-boot directory** Assign this value

```bash
# Set the Cross Compiler into the environment
# To be used by the u-boot
export CROSS_COMPILE=arm-linux-gnueabihf-
export ARCH=arm

# load the default configuration of rpi 3
make rpi_4_32b_defconfig
```

**In case of 64 architecture**

```bash
export CROSS_COMPILE=aarch64-linux-gnu-
export ARCH=arm64

# depends what raspberry pi in used
make rpi_4_b_defconfig
```

#### Beaglebone

In **U-boot directory** Assign this value

```bash
# Set the Cross Compiler into the environment
# To be used by the u-boot
export CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm

# load the default configuration of ARM Vexpress Cortex A9
make am335x_evm_defconfig
```

### Configure U-Boot 

In this part we need to configure some u-boot configuration for the specific board chosen up.

```bash
make menuconfig
```

**The customer requirement are like following**:

- [ ] Support **editenv**.
- [ ] Support **bootd**.
- [ ] Store the environment variable inside file call **uboot.env**.
- [ ] Unset support of **Flash**
- [ ] Support **FAT file system**
  - [ ] Configure the FAT interface to **mmc**
  - [ ] Configure the partition where the fat is store to **0:1**

# Emulated SD Card

## SD Card

In this section it's required to have SD card with first partition to be FAT as pre configured in **U-boot Menuconfig**.

### ! ONLY FOR WHO WORK WITH QEMU !

In order to Emulate SD card to attached to Qemu following steps will be followed: (ONLY FOR NON PHYSICAL SD):

```bash
# Change directory to the directory before U-Boot
cd ..

# Create a file with 1 GB filled with zeros
dd if=/dev/zero of=sd.img bs=1M count=1024
```

### ! ONLY FOR WHO WORK WITH HW !

Plug your SD card to the computer

```bash
# To show where your sd card is mounted
lsblk 
```

`WARNING: The following command will completely erase all data on the specified SD card.`

```bash
### WARNING ####
sudo dd if=/dev/zero of=/dev/mmblk<x> bs=1M

# is not always mmblck to make sure use the command lsblk

# Assign the Block device as global variable to be treated as MACRO
export DISK=/dev/mmblck<x>
```



### Configure the Partition Table for the SD card

```bash
# for the VIRTUAL SD card
cfdisk sd.img

# for Physical SD card
cfdisk /dev/mmblck<x>
```

| Partition Size | Partition Format | Bootable  |
| :------------: | :--------------: | :-------: |
|    `200 MB`    |     `FAT 16`     | ***Yes*** |
|    `300 MB`    |     `Linux`      | ***No***  |

**write** to apply changes

### Loop Driver FOR Virtual usage ONLY

To emulate the sd.img file as a sd card we need to attach it to **loop driver** to be as a **block storage**

```bash
# attach the sd.img to be treated as block storage
sudo losetup -f --show --partscan sd.img

# Running the upper command will show you
# Which loop device the sd.img is connected
# take it and assign it like down bellow command

# Assign the Block device as global variable to be treated as MACRO
export DISK=/dev/loop<x>
```

### Format Partition Table

As pre configured from **cfdisk command** first partition is **FAT**

```bash
# Formating the first partition as FAT
sudo mkfs.vfat -F 16 -n boot ${DISK}p1
```

 As pre configured from cfdisk Command second partition is linux

```bash
# format the created partition by ext4
sudo mkfs.ext4 -L rootfs ${DISK}p2
```
## qemuBashScript Run First Time
```bash
#!/bin/bash

# Create loop device
loop=$(sudo losetup -f --show --partscan "$SD_IMG")

# Check if loop device was successfully created
if [ $? -ne 0 ]; then
    echo "Failed to create loop device. Exiting."
    exit 1
fi

# Format and mount boot partition
sudo mkfs.vfat -F 16 -n boot "$loop"p1

# Check if formatting was successful
if [ $? -ne 0 ]; then
    echo "Failed to format boot partition. Exiting."
    exit 1
#fi

sudo mount "$loop"p1 "$SD_1_2/sd1/"

# Check if mount was successful
if [ $? -ne 0 ]; then
    echo "Failed to mount boot partition. Exiting."
    exit 1
fi

# Format and mount rootfs partition
sudo mkfs.ext4 -L rootfs "$loop"p2

# Check if formatting was successful
if [ $? -ne 0 ]; then
    echo "Failed to format rootfs partition. Exiting."
    exit 1
fi

sudo mount "$loop"p2 "$SD_1_2/sd2/"

# Check if mount was successful
if [ $? -ne 0 ]; then
    echo "Failed to mount rootfs partition. Exiting."
    exit 1
fi

lsblk

echo "Script executed successfully."
```
### To use script again make (mkfs) line Comment 

## Test U-Boot

Check the **u-boot** and the **sd card** are working

### Vexpress-a9 (QEMU)

Start Qemu with the **Emulated SD** card

```bash
qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot/u-boot \
-sd sd.img
```

### Raspberry Pi

Add all **close source** file provided my Raspberry depend for each version to the **SD card in FAT Partition**

```
1. Bootcode.bin 
2. Fixup.dat
3. cmdline.txt
4. config.txt
5. start.elf
6. u-boot.bin {generated from u-boot}
```

Edit file `config.txt` as following

```
kernel=u-boot.bin
enable_uart=1
```

### Beaglebone

Add following file generated by U-Boot in the SD card FAT partition

```
1. MLO
2. u-boot.bin
```

## Initialize TFTP protocol

### Ubuntu

```bash
#Switch to root
sudo su
#Make sure you are connected to internet
ping google.com
#Download tftp protocol
sudo apt-get install tftpd-hpa
#Check the tftp ip address
ip addr `will be needed`
#Change the configuration of tftp
nano /etc/default/tftpd-hpa
	#write inside the file
    tftf_option = “--secure –-create”
#Restart the protocal
Systemctl restart tftpd-hpa
#Make sure the tftp protocol is running
Systemctl status tftpd-hpa
#Change the file owner
cd /srv
chown tftp:tftp tftp 
#Move your image or file to the server
cp [File name] /srv/tftp
```

### Create Virtual Ethernet For QEMU

This section for Qemu emulator users only **no need for who using HW**

Create a script `qemu-ifup` 

```bash
#!/bin/sh
ip a add 192.168.0.1/24 dev $1
ip link set $1 up
```

#### Start Qemu

In order to start Qemu with the new virtual ethernet

```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot/u-boot \
-sd sd.img \
-net tap,script=./qemu-ifup -net nic
```

## Setup U-Boot IP address

```bash
#Apply ip address for embedded device
setenv ipaddr [chose]
#Set the server ip address that we get from previous slide
setenv serverip [host ip address]

#### WARNING ####
#the ip address should has the same net mask

```

## Load File to RAM

First we need to know the ram address by running the following commend

```bash
# this commend will show all the board information and it start ram address
bdinfo
```

### Load from FAT

```bash
# addressRam is a variable knowen from bdinfo commend
fatload mmc 0:1 [addressRam] [fileName]
```

### Load from TFTP

```bash
# addressRam is a variable knowen from bdinfo commend
tftp [addressRam] [fileName]
```



## Write Script in U-boot

```bash
setenv ifcondition "if mmc dev; then echo MmcExist; elif mtd list; then echo NoDeviceExist; else echo noDeviceExist; fi"
```

# U-boot Commands

### help Command
	- ==> help
### U-Boot information commands
	- Version details: 
		- ==> version
	- NAND flash information:
		- ==> nand info
	- MMC information:
		- ==> mmc info
	- Board information:
		- ==> bdinfo
### U-Boot environment commands
	- Shows all variables
		- ==> printenv
	- Shows the value of a variable
		- ==> printenv <variable-name>
	- Changes the value of a variable or defines a new one, only in RAM
		- ==> setenv <variable-name> <variable-value>
	- Interactively edits the value of a variable, only in RAM
		- ==> editenv <variable-name>
	- Saves the current state of the environment to storage for persistence.
		- ==> saveenv
	- env command, with many sub-commands: env default, env info, env erase,
env set, env save, etc.

### U-Boot Commands to inspect or modify any memory location
	- Memory display
		- ==> md [.b, .w, .l, .q] address [# of objects]
	- Memory write
		- ==> mw [.b, .w, .l, .q] address value [count]
	- Memory modify (modify memory contents interactively starting from address)
		- ==> mm [.b, .w, .l, .q] address

### U-Boot filesystem storage commands
	- #### U-Boot has support for many filesystems
		- The exact list of supported filesystems depends on the U-Boot configuration
	- ####  Per-filesystem commands
		- FAT: fatinfo, fatls, fatsize, fatload, fatwrite
		- ext2/3/4: ext2ls, ext4ls, ext2load, ext4load, ext4size, ext4write
		- Squashfs: sqfsls, sqfsload
	- ####  “New” generic commands, working for all filesystem types
		- Load a file: load <interface> [<dev[:part]> [<addr> [<filename> [bytes [pos]]]]]
		- List files: ls <interface> [<dev[:part]> [directory]]
		- Get the size of a file: size <interface> <dev[:part]> <filename> (result stored in filesize environment variable)
		- interface: mmc, usb
		- dev: device number, 0 for first device, 1 for second device
		- part: partition number

### U-Boot Environment variables
	- ethaddr: MAC address
	- ipaddr: IP address of the board
	- serverip: IP address of the server for network related commands
### U-Boot Important commands
	- ping: ping a destination machine. Note: U-Boot is not an operating system with multitasking/interrupts, so ping from another machine to U-Boot cannot work.
	- tftp: load a file using the TFTP protocol
	- dhcp: get an IP address using DHCP
```
#### (TFTP) Trivial File Transfer Protocol
- TFTP Network transfer from the development workstation to U-Boot on the target takes place through TFTP
```

### Environment variables can contain small scripts, to execute several commands and test the results of commands.
	- Useful to automate booting or upgrade processes
	- Several commands can be chained using the ; operator
	- Tests can be done using if command ; then ... ; else ... ; fi
	- Scripts are executed using run <variable-name>
	- You can reference other variables using ${variable-name}
	- #### Examples
	'''
	- setenv bootcmd 'tftp 0x21000000 zImage; tftp 0x22000000 dtb; bootz
	0x21000000 - 0x22000000'
	- setenv mmc-boot 'if fatload mmc 0 80000000 boot.ini; then source; else
	if fatload mmc 0 80000000 zImage; then run mmc-do-boot; fi; fi'
	'''
### U-Boot booting commands
- #### Commands to boot a Linux kernel image
	- bootz → boot a compressed ARM32 zImage
	- booti → boot an uncompressed ARM64 or RISC-V Image
	- bootm → boot a kernel image with legacy U-Boot headers
	- zboot → boot a compressed x86 bzImage
- #### bootz [addr [initrd[:size]] [fdt]]
	- addr: address of the kernel image in RAM
	- initrd: address of the initrd or initramfs, if any. Otherwise, must pass -
	- fdt: address of the Device Tree passed to the Linux kernel
- #### Important environment variables
	- bootcmd: list of commands executed automatically by U-Boot after the count down
	- bootargs: Linux kernel command line

### Generic Distro boot
- kernel_addr_r: address in RAM to load the kernel image
- ramdisk_addr_r: address in RAM to load the initramfs image (if any)
- fdt_addr_r: address in RAM to load the DTB (Flattened Device Tree)
- pxefile_addr_r: address in RAM to load the configuration file (usually extlinux.conf)
- bootfile: the path to the configuration file, for example /boot/extlinux/extlinux.conf



