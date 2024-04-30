# The Linux Kernel API
### [kernel.org](https://docs.kernel.org/)
# [char devices](https://docs.kernel.org/core-api/kernel-api.html?highlight=register_chrdev#char-devices)

```c
int register_chrdev_region(dev_t from, unsigned count, const char *name);
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
void unregister_chrdev_region(dev_t from, unsigned count);
int cdev_add(struct cdev *p, dev_t dev, unsigned count);
void cdev_set_parent(struct cdev *p, struct kobject *kobj);
int cdev_device_add(struct cdev *cdev, struct device *dev);
void cdev_device_del(struct cdev *cdev, struct device *dev);
void cdev_del(struct cdev *p);
struct cdev *cdev_alloc(void);
void cdev_init(struct cdev *cdev, const struct file_operations *fops);
```

## register a range of device numbers
```c
int register_chrdev_region(dev_t from, unsigned count, const char *name);
```
**Parameters**

- **dev_t from**
    the first in the desired range of device numbers; must include the major number.

- **unsigned count**
    the number of consecutive (minor) device numbers required

- **const char *name**
    the name of the device or driver.

**Description**
    Return value is zero on success, a negative error code on failure.

## Allocates a range of char device numbers. The major number will be chosen dynamically

```c
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
```
**Parameters**

- **dev_t *dev**
    output parameter for first assigned number

- **unsigned baseminor**
    first of the requested range of minor numbers

- **unsigned count**
    the number of minor numbers required

- **const char *name**
    the name of the associated device or driver

**Description**
    Allocates a range of char device numbers. The major number will be chosen dynamically, and returned (along with the first minor number) in dev. Returns zero or a negative error code.


## Create and Register a cdev occupying a range of minors

```c
int __register_chrdev(unsigned int major, unsigned int baseminor, unsigned int count, const char *name, const struct file_operations *fops);
```
**Parameters**

- **unsigned int major**
    major device number or 0 for dynamic allocation

- **unsigned int baseminor**
    first of the requested range of minor numbers

- **unsigned int count**
    the number of minor numbers required

- **const char *name**
    name of this range of devices

- **const struct file_operations *fops**
    file operations associated with this devices

**Description**

- If major == 0 this functions will dynamically allocate a major and return its number.

- If major > 0 this function will attempt to reserve a device with the given major number and will return zero on success.

- Returns a -ve errno on failure.

The name of this device has nothing to do with the name of the device in /dev. It only helps to keep track of the different owners of devices. If your module name has only one type of devices it’s ok to use e.g. the name of the module here.

## unregister a range of device numbers
```c
void unregister_chrdev_region(dev_t from, unsigned count);
```
**Parameters**

- **dev_t from**
    the first in the range of numbers to unregister

- **unsigned count**
    the number of device numbers to unregister

**Description**

    This function will unregister a range of count device numbers, starting with from.
    The caller should normally be the one who allocated those numbers in the first place...

# unregister and destroy a cdev

```c
void __unregister_chrdev(unsigned int major, unsigned int baseminor, unsigned int count, const char *name);
```
**Parameters**

- **unsigned int major**
    major device number

- **unsigned int baseminor**
    first of the range of minor numbers

- **unsigned int count**
    the number of minor numbers this cdev is occupying

- **const char *name**
    name of this range of devices

**Description**

    Unregister and destroy the cdev occupying the region described by major, baseminor and count.
    This function undoes what __register_chrdev() did.

## add a char device to the system

```c
int cdev_add(struct cdev *p, dev_t dev, unsigned count);
```
**Parameters**

- **struct cdev *p**
    the cdev structure for the device

- **dev_t dev**
    the first device number for which this device is responsible

- **unsigned count**
    the number of consecutive minor numbers corresponding to this device

**Description**

    cdev_add() adds the device represented by p to the system, making it live immediately. A negative error code is returned on failure.

## set the parent kobject for a char device

```c
void cdev_set_parent(struct cdev *p, struct kobject *kobj);
```
**Parameters**

- **struct cdev *p**
    the cdev structure

- **struct kobject *kobj**
    the kobject to take a reference to

**Description**

    cdev_set_parent() sets a parent kobject which will be referenced appropriately so the parent is not freed before the cdev.
    This should be called before cdev_add.

## add a char device and it’s corresponding struct device, linkink

```c
int cdev_device_add(struct cdev *cdev, struct device *dev);
```
**Parameters**

- **struct cdev *cdev**
    the cdev structure

- **struct device *dev**
    the device structure

**Description**

- cdev_device_add() adds the char device represented by cdev to the system, just as cdev_add does. It then adds dev to the system using device_add The dev_t for the char device will be taken from the struct device which needs to be initialized first. This helper function correctly takes a reference to the parent device so the parent will not get released until all references to the cdev are released.

- This helper uses dev->devt for the device number. If it is not set it will not add the cdev and it will be equivalent to device_add.

- This function should be used whenever the struct cdev and the struct device are members of the same structure whose lifetime is managed by the struct device.

**NOTE**

    Callers must assume that userspace was able to open the cdev and can call cdev fops callbacks at any time, even if this function fails.

## inverse of cdev_device_add

```c
void cdev_device_del(struct cdev *cdev, struct device *dev);
```
**Parameters**

- **struct cdev *cdev**
    the cdev structure

- **struct device *dev**
    the device structure

**Description**

- cdev_device_del() is a helper function to call cdev_del and device_del. It should be used whenever cdev_device_add is used.

- If dev->devt is not set it will not remove the cdev and will be equivalent to device_del.

**NOTE**

    This guarantees that associated sysfs callbacks are not running or runnable,
    however any cdevs already open will remain and their fops will still be callable even after this function returns.

## remove a cdev from the system

```c
void cdev_del(struct cdev *p);
```
**Parameters**

- **struct cdev *p**
    the cdev structure to be removed

**Description**

- cdev_del() removes p from the system, possibly freeing the structure itself.

**NOTE**

    This guarantees that cdev device will no longer be able to be opened,
    however any cdevs already open will remain and their fops will still be callable even after cdev_del returns.



## allocate a cdev structure

```c
struct cdev *cdev_alloc(void);
```
**Parameters**

- **void**
    no arguments

**Description**

    Allocates and returns a cdev structure, or NULL on failure.

## initialize a cdev structure

```c
void cdev_init(struct cdev *cdev, const struct file_operations *fops);
```
**Parameters**

- **struct cdev *cdev**
    the structure to initialize

- **const struct file_operations *fops**
    the file_operations for this device

**Description**

    Initializes cdev, remembering fops, making it ready to add to the system with cdev_add().