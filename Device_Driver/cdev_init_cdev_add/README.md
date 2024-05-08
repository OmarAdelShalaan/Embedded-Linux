# cdev_init & cdev_add


## cdev_init

The cdev_init function initializes a character device (struct cdev) with the specified file operations (struct file_operations). This function is typically used in Linux kernel programming for managing character devices.

```c
/**
 * cdev_init() - initialize a cdev structure
 * @cdev: the structure to initialize
 * @fops: the file_operations for this device
 *
 * Initializes @cdev, remembering @fops, making it ready to add to the
 * system with cdev_add().
 */
void cdev_init(struct cdev *cdev, const struct file_operations *fops);
```

## cdev_add

The cdev_add function is used in Linux kernel programming to add a character device (struct cdev) to the system. It associates the character device with a device number (dev_t) and specifies the number of minor devices (count) that are associated with this major device.

```c
/**
 * cdev_add() - add a char device to the system
 * @p: the cdev structure for the device
 * @dev: the first device number for which this device is responsible
 * @count: the number of consecutive minor numbers corresponding to this
 *         device
 *
 * cdev_add() adds the device represented by @p to the system, making it
 * live immediately.  A negative error code is returned on failure.
 */
int cdev_add(struct cdev *p, dev_t dev, unsigned count);
```

## class_create

The class_create function in Linux kernel programming is used to create a device class. Device classes are used to group devices that belong to the same category or have similar functionalities. This function is typically used when working with device drivers to organize devices in a systematic way.


```c
/**
 * class_create - create a struct class structure
 * @name: pointer to a string for the name of this class.
 *
 * This is used to create a struct class pointer that can then be used
 * in calls to device_create().
 *
 * Returns &struct class pointer on success, or ERR_PTR() on error.
 *
 * Note, the pointer created here is to be destroyed when finished by
 * making a call to class_destroy().
 */
struct class *class_create(const char *name);
```

## device_create

The device_create function in Linux kernel programming is used to create a device and register it with the kernel. This function is typically used in device drivers to create device nodes in the /dev directory and associate them with a device class.

```c
/**
 * device_create - creates a device and registers it with sysfs
 * @class: pointer to the struct class that this device should be registered to
 * @parent: pointer to the parent struct device of this new device, if any
 * @devt: the dev_t for the char device to be added
 * @drvdata: the data to be added to the device for callbacks
 * @fmt: string for the device's name
 *
 * This function can be used by char device classes.  A struct device
 * will be created in sysfs, registered to the specified class.
 *
 * A "dev" file will be created, showing the dev_t for the device, if
 * the dev_t is not 0,0.
 * If a pointer to a parent struct device is passed in, the newly created
 * struct device will be a child of that device in sysfs.
 * The pointer to the struct device will be returned from the call.
 * Any further sysfs files that might be required can be created using this
 * pointer.
 *
 * Returns &struct device pointer on success, or ERR_PTR() on error.
 */
struct device *device_create(const struct class *class, struct device *parent, dev_t devt, void *drvdata, const char *fmt, ...);

```

## class_destroy

The class_destroy function in Linux kernel programming is used to destroy a previously created device class. This function is typically used to clean up resources associated with a device class when it is no longer needed, such as during module unloading or device driver cleanup.

```c
/**
 * class_destroy - destroys a struct class structure
 * @cls: pointer to the struct class that is to be destroyed
 *
 * Note, the pointer to be destroyed must have been created with a call
 * to class_create().
 */
void class_destroy(const struct class *cls);
```

## cdev_del

The cdev_del function in Linux kernel programming is used to delete a character device (struct cdev) from the system. It's typically used when you want to remove a character device that was previously added using cdev_add.

```c
/**
 * cdev_del() - remove a cdev from the system
 * @p: the cdev structure to be removed
 *
 * cdev_del() removes @p from the system, possibly freeing the structure
 * itself.
 *
 * NOTE: This guarantees that cdev device will no longer be able to be
 * opened, however any cdevs already open will remain and their fops will
 * still be callable even after cdev_del returns.
 */
void cdev_del(struct cdev *p);
```

## device_destroy

The device_destroy function in Linux kernel programming is used to destroy a device that was previously created with device_create. This function is typically used to clean up resources associated with a device when it is no longer needed, such as during module unloading or device driver cleanup.

```c
/**
 * device_destroy - removes a device that was created with device_create()
 * @class: pointer to the struct class that this device was registered with
 * @devt: the dev_t of the device that was previously registered
 *
 * This call unregisters and cleans up a device that was created with a
 * call to device_create().
 */
void device_destroy(const struct class *class, dev_t devt);
```



