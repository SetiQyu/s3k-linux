
## Notes

All the steps have been tested only for the given versions of things. Newer versions of different components may or may not work.

Linux has to be built from a native Linux system. There are many steps to creating a working binary. Depending on how powerful your computer is this can take a while (building Linux in particular).

For most of the steps you need a toolchain capable of running on your host hardware but emit code to RISCV64 (AKA a cross-compiler toolchain). [Here](https://skarnet.org/toolchains/) a full prebuilt toolchain can be found however others could also be used.

The instructions are written from the perspective of a Fedora 43/44 distro. If you have any other mainstream and orthodox Linux distro then this should all be fine however you might have to find out what the different package names are.

You will need to build several different components to create the kernel binary as outlined here, including the filesystem, userland and DTB as they all need to be baked into the Linux binary itself. They all need to be created before building Linux which is the final step.

## Device-tree

### Prereqs

- The dts file from this repo
- dts to dtb compiler (e.g `dnf install dtc`)

### Steps

Install the package `dtc`. Then run it on the dts file to produce a dtb. Your command should look something like `dtc -I dts -O dtb -o /path/to/dtb_file/result.dtb /path/to/dts_file/out.dts`. Once you have a dtb you are done.

## Busybox

NOTE: This step can be skipped if you simply use the `initramfs.cpio.gz` from the repo. This is only if you want to modify the userland in Linux.

### Prereqs

- Busybox 1.36.1
- Config file from this repo
- A cross-compiler toolchain that emits RISCV64
- The `initramfs` directory and contents from this repo (only if you don`t want to setup the userland yourself)

### Steps

Download and extract busybox. Move the config file into the busybox root dir and make sure to rename it to `.config`. Run `make -j$(nproc) ARCH=riscv CROSS_COMPILE=/path/to/cross/compile/toolchain/riscv64-linux-musl-` (note the trailing dash). Then `make install`.

Then follow the steps [here](https://web.archive.org/web/20260310183606/https://cylab.be/blog/320/build-a-kernel-initramfs-and-busybox-to-create-your-own-micro-linux) under the initramfs section.

Once you are done you should have a `initramfs.cpio.gz` which contains what the Linux kernel will execute if it boots succesfully to userland.

## Linux

### Prereqs

- Linux 6.18.9 full source dir (https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.18.19.tar.xz)
- Prequisites for building Linux (the exact packages to download varies from distro to distro)
- RISCV cross-compiler toolchain capable of building Linux
- Patch files in this repo
- Kernel config file in this repo

### Steps

Download and extract a tarball of the given Linux version. Move the Kconfig file into the root of Linux. Copy the dtb file to ``/linux_source_dir/arch/riscv/boot/dts/`` make sure it is named `out.dtb`. Move the `s3k.h` and `irq-sifive-plic.c` file to `linux_source/drivers/irqchip/`. Then run `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`, you will be faced with the Linux build config menu. Here you will need to modify the paths to the various build artefacts you have created.

Go to `General Setup` and scroll down to the `Initial RAM filesystem and RAM disk (initramfs/initrd) support` option and change the path to your `initramfs.cpio.gz` path. Quit the build menu.

Now you should be able to build the kernel. Your build command should look something like `make -j$(nproc) ARCH=riscv CROSS_COMPILE="/path/to/cross/compile/toolchain/riscv64-linux-musl-"` (note the trailing dash).

This will take a long while depending on how powerful your computer is. If everything went well you will have the kernel binary located in `linux_source/arch/riscv/boot/Image`. This is the binary that s3k will execute.
