IMAGE_FSTYPES

wic:
Stands for "Yocto wic (WIC) image format."
Includes a bootloader, kernel, root filesystem, and partition layout.
Suitable for creating bootable SD card or USB images.
ext4:
Creates an ext4 filesystem image.
Suitable for use with devices that support ext4 filesystems.
tar:
Generates a tar archive of the root filesystem.
Can be extracted onto a storage device or used for backup purposes.
tar.gz or tgz:
Similar to tar but compressed using gzip.
Reduces the size of the archive for storage or distribution.
squashfs:
Creates a squashfs filesystem image.
Provides read-only compressed filesystem suitable for embedded devices.
jffs2:
Generates a JFFS2 filesystem image.
Used for devices that support JFFS2, such as some flash memory systems.
ubifs:
Creates an UBIFS filesystem image.
Designed for devices with UBIFS support, often used in NAND flash storage.
iso:
Generates an ISO image.
Suitable for creating CD or DVD images.
cramfs:
Creates a CRAMFS filesystem image.
Provides a read-only compressed filesystem, often used in older embedded systems.
cpio:
Generates a cpio archive of the root filesystem.
Similar to tar but with a different format.
