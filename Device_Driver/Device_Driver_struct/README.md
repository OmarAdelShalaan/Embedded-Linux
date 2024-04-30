# The Linux Kernel API
### [kernel.org](https://docs.kernel.org/)
# [Device Driver-Model Structures](https://docs.kernel.org/driver-api/infrastructure.html#c.device_driver)

# The Basic Device Driver-Model Structures 
```c
struct cdev *cdev_alloc(void);
struct class{};
struct device_driver{};
struct file_operations {};
```
## allocate a cdev structure

```c
struct cdev *cdev_alloc(void);
```
**Parameters**

- **void**
    no arguments

**Description**

    Allocates and returns a cdev structure, or NULL on failure.

## struct device_driver

```c
struct device_driver {
    const char              *name;
    const struct bus_type   *bus;
    struct module           *owner;
    const char              *mod_name;
    bool suppress_bind_attrs;
    enum probe_type probe_type;
    const struct of_device_id       *of_match_table;
    const struct acpi_device_id     *acpi_match_table;
    int (*probe) (struct device *dev);
    void (*sync_state)(struct device *dev);
    int (*remove) (struct device *dev);
    void (*shutdown) (struct device *dev);
    int (*suspend) (struct device *dev, pm_message_t state);
    int (*resume) (struct device *dev);
    const struct attribute_group **groups;
    const struct attribute_group **dev_groups;
    const struct dev_pm_ops *pm;
    void (*coredump) (struct device *dev);
    struct driver_private *p;
};
```
**Members**

- **name**
    Name of the device driver.

- **bus**
    The bus which the device of this driver belongs to.

- **owner**
    The module owner.

- **mod_name**
    Used for built-in modules.

- **suppress_bind_attrs**
    Disables bind/unbind via sysfs.

- **probe_type**
    Type of the probe (synchronous or asynchronous) to use.

- **of_match_table**
    The open firmware table.

- **acpi_match_table**
    The ACPI match table.

- **probe**
    Called to query the existence of a specific device,
    whether this driver can work with it, and bind the driver to a specific device.

- **sync_state**
    Called to sync device state to software state after all the state tracking consumers linked to this device
    (present at the time of late_initcall) have successfully bound to a driver.
    If the device has no consumers, this function will be called at late_initcall_sync level.
    If the device has consumers that are never bound to a driver, this function will never get called until they do.

- **remove**
    Called when the device is removed from the system to unbind a device from this driver.

- **shutdown**
    Called at shut-down time to quiesce the device.

- **suspend**
    Called to put the device to sleep mode. Usually to a low power state.

- **resume**
    Called to bring a device from sleep mode.

- **groups**
    Default attributes that get created by the driver core automatically.

- **dev_groups**
    Additional attributes attached to device instance once it is bound to the driver.

- **pm**
    Power management operations of the device which matched this driver.

- **coredump**
    Called when sysfs entry is written to. The device driver is expected to call the dev_coredump API resulting in a uevent.

- **p**
    Driver core’s private data, no one other than the driver core can touch this.

**Description**

    The device driver-model tracks all of the drivers known to the system.
    The main reason for this tracking is to enable the driver core to match up drivers with new devices.
    Once drivers are known objects within the system, however, a number of other things become possible.
    Device drivers can export information and configuration variables that are independent of any specific device.

## struct class
```c
struct class {
    const char              *name;
    const struct attribute_group    **class_groups;
    const struct attribute_group    **dev_groups;
    int (*dev_uevent)(const struct device *dev, struct kobj_uevent_env *env);
    char *(*devnode)(const struct device *dev, umode_t *mode);
    void (*class_release)(const struct class *class);
    void (*dev_release)(struct device *dev);
    int (*shutdown_pre)(struct device *dev);
    const struct kobj_ns_type_operations *ns_type;
    const void *(*namespace)(const struct device *dev);
    void (*get_ownership)(const struct device *dev, kuid_t *uid, kgid_t *gid);
    const struct dev_pm_ops *pm;
};
```
**Members**

- **name**
    Name of the class.

- **class_groups**
    Default attributes of this class.

- **dev_groups**
    Default attributes of the devices that belong to the class.

- **dev_uevent**
    Called when a device is added, removed from this class, or a few other things that generate uevents to add the environment variables.

- **devnode**
    Callback to provide the devtmpfs.

- **class_release**
    Called to release this class.

- **dev_release**
    Called to release the device.

- **shutdown_pre**
    Called at shut-down time before driver shutdown.

- **ns_type**
    Callbacks so sysfs can detemine namespaces.

- **namespace**
    Namespace of the device belongs to this class.

- **get_ownership**
    Allows class to specify uid/gid of the sysfs directories for the devices belonging to the class. Usually tied to device’s namespace.

- **pm**
    The default device power management operations of this class.

**Description**

    A class is a higher-level view of a device that abstracts out low-level implementation details.
    Drivers may see a SCSI disk or an ATA disk, but, at the class level, 
    they are all simply disks. Classes allow user space to work with devices based on what they do,
    rather than how they are connected or how they work.




## struct file_operations 
[link](https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L1983)
```c
struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
	int (*iopoll)(struct kiocb *kiocb, struct io_comp_batch *,
			unsigned int flags);
	int (*iterate_shared) (struct file *, struct dir_context *);
	__poll_t (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	unsigned long mmap_supported_flags;
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	void (*splice_eof)(struct file *file);
	int (*setlease)(struct file *, int, struct file_lock **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabilities)(struct file *);
#endif
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,
			loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *file_in, loff_t pos_in,
				   struct file *file_out, loff_t pos_out,
				   loff_t len, unsigned int remap_flags);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
	int (*uring_cmd)(struct io_uring_cmd *ioucmd, unsigned int issue_flags);
	int (*uring_cmd_iopoll)(struct io_uring_cmd *, struct io_comp_batch *,
				unsigned int poll_flags);
} __randomize_layout;
```