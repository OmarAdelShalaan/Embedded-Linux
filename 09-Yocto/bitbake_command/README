$ git clone -b dunfell git://git.yoctoproject.org/poky.git
$ source poky/oe-init-build-env

$ bitbake core-image-minimal

$ source poky/oe-init-build-env build-nova

$ bitbake-layers create-layer nova

$ bitbake-layers add-layer ../meta-nova

$ bitbake-layers show-layers

$ bitbake -c listtasks core-image-minimal


To get the code for a target and all its dependencies, which is useful when you want to
make sure you have downloaded all the code for the image you are about to build, use the
following command:
$ bitbake core-image-minimal --runall=fetch