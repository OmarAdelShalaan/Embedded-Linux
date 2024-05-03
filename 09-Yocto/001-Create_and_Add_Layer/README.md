# Create and Add Layer with Yocto 

## show layer
```bash
$ bitbake-layers show-layers
```

![showlayers.jpg](./showlayers.jpg)

## Create Layer
```bash
$ bitbake-layers create-layer ../meta-my_layer
```

![createLayer.jpg](./createLayer.jpg)

## Add Layer
```bash
$ bitbake-layers add-layer ../meta-my_layer
```

![addLayer.jpg](./addLayer.jpg)

## show layer
```bash
$ bitbake-layers show-layers
# OR
$ cat ./conf/bblayers.conf
```

![newlayer.jpg](./newlayer.jpg)
