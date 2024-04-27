# Device Driver
```
A device driver is a software component that allows the operating system to communicate with a hardware device.
It acts as an intermediary between applications or higher-level software and the hardware itself
```
### Purpose of Device Drivers:
- Device drivers enable the operating system to control and interact with hardware devices such as disk drives, network cards, graphics cards, USB devices, and more.
- They abstract hardware-specific details and provide a standardized interface for applications to access and use hardware functionalities.
### Types of Device Drivers:
- **Character Drivers:** Handle character-oriented devices, such as terminals, serial ports, and printers. They deal with data character by character.
- **Block Drivers:** Manage block-oriented devices like hard drives and flash drives. They work with data in blocks or chunks.
- **Network Drivers:** Facilitate communication with network devices like Ethernet adapters and wireless cards.
- **Filesystem Drivers:** Control access to different types of filesystems such as ext4, NTFS, and FAT32.
### Components of Device Drivers:
- **Initialization and Cleanup Functions:** Typically defined using **module_init** and **module_exit** macros. They handle device initialization and cleanup operations.
- **File Operations (fops):** Implement functions like open, read, write, close, etc., allowing user-space applications to interact with the device.
- **Data Structures:** Include structures like **file_operations**, **device_driver**, **platform_driver**, and others, which define driver behaviors and configurations.
- **Device Registration:** Involves registering the driver with the kernel to make it accessible to the system.
### Driver Development Process:
- Identify the hardware device and its specifications.
- Write the driver code, including initialization, file operations, and cleanup functions.
- Compile the driver into a loadable kernel module (**.ko** file) or build it directly into the kernel.
### Kernel Module vs. Built-in Driver:
**Kernel Module:** A driver compiled separately from the kernel and **loaded dynamically**. Provides flexibility for adding, removing, and updating drivers without rebooting.
**Built-in Driver:** **Compiled directly into the kernel image**. Offers faster initialization and lower overhead but requires rebuilding and rebooting the kernel to update or change drivers.

## [Hello Kernel Module](./hello_kernel/) 

### Makefile 
```Makefile
obj-m += hello_kernel.o  # Specify the module name correctly
                         # m according that is module
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
    # (C: Change Dir) (uname -r: for kernel header)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean  
```
## obj-
 ```
 Linux kernel module development and Makefiles, obj- is a prefix used to specify different types of objects or targets for the kernel build system.
```
- **obj-m:** This prefix is used to specify modules that should be built as loadable kernel modules (.ko files). For example:
```Makefile
obj-m += hello_kernel.o
# This line tells the build system to build hello_kernel.c into a loadable kernel module named hello_kernel.ko.
```
- **obj-y:** This prefix is used to specify modules that should be built directly into the kernel image. These modules become part of the monolithic kernel. For example:
```Makefile
obj-y += core_module.o
# This line tells the build system to build core_module.c and include it directly in the kernel image.
```
- **obj-n:** This prefix is used to specify modules that should not be built at all. It's typically used when conditional compilation is involved and certain modules are excluded based on configuration options.

**obj:** This prefix is a generic prefix and is sometimes used without any suffix (obj-) to specify a mix of modules that can be built as loadable modules or directly into the kernel, depending on configuration.
For example, a typical Makefile for a kernel module might include lines like these:
```Makefile
obj-m += hello_kernel.o
obj-y += core_module.o
obj-$(CONFIG_FEATURE_MODULE) += feature_module.o
```
**In this example:**
hello_kernel.o will be built as a loadable kernel module.
core_module.o will be built directly into the kernel image.
feature_module.o will be built as a loadable module only if the CONFIG_FEATURE_MODULE configuration option is enabled.

### Kernel Command 
- **insmod** to load a kernel module (specified by the **.ko** file).
- **rmmod** to unload a kernel module (specified by its module name).
- **dmesg** to view kernel logs, including module-related messages.


