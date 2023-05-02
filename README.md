# meta-xt-prod-cockpit-rcar - Demo product with advanced HMP technologies
meta-xt-prod-cockpit-rcar

This repository contains Renesas RCAR Gen3-specific Yocto layers for
Xen Troops demo and moulin project file to build it. Layers in this
repository provide final recipes to build meta-xt-prod-cockpit-rcar demo.
This demo is the main Xen Troops product, that we use to develop and
integrate new features

Those layers may be added and used manually, but they were written
with [Moulin](https://moulin.readthedocs.io/en/latest/) build system,
as Moulin-based project files provide correct entries in local.conf

# Moulin project file

Features that are present :
* Kingfisher with Starter Kit Premiere 8GB board
* SD or eMMC boot
* Android VM support

# Building
## Requirements

1. Ubuntu 18.0+ or any other Linux distribution which is supported by Poky/OE
2. Development packages for Yocto. Refer to Yocto manual.
3. You need Moulin installed in your PC. Recommended way is to install it for your user only: pip3 install --user git+https://github.com/xen-troops/moulin. Make sure that your PATH environment variable includes ${HOME}/.local/bin.
4. Ninja build system: sudo apt install ninja-build on Ubuntu

## Fetching

You can fetch/clone this whole repository, but you actually need only one file from it: prod-cockpit-rcar.yaml. During build moulin will fetch this repository again into yocto/ directory. So, to reduce possible confuse, we recommend to download only prod-cockpit-rcar.yaml:

```
# curl -O https://raw.githubusercontent.com/xen-troops/meta-xt-prod-cockpit-rcar/master/prod-cockpit-rcar.yaml
```

## Building

Moulin is used to generate Ninja build file: moulin prod-cockpit-rcar.yaml. This project have provides number of additional options. You can use check them with --help-config command line option:

```
# moulin prod-cockpit-rcar.yaml --help-config
usage: moulin prod-cockpit-rcar.yaml --MACHINE h3ulcb-4x2g-kf --ENABLE_ANDROID yes --ENABLE_CLUSTER yes --ENABLE_TOOLS yes
       
Config file description: Xen-Troops development setup for Renesas RCAR Gen3
hardware

optional arguments:
  --MACHINE {h3ulcb-4x2g-kf}
                        RCAR Gen3-based device
  --ENABLE_ANDROID {no,yes}
                        Build Android as a guest VM
  --ENABLE_CLUSTER {no,yes}
                        Build Instrument Cluster application.
  --ENABLE_TOOLS {no. yes}
  			Build the tool (cr7-image-gen). This application
			allows generating the source files from the list of the images 
			required for cr7.
  --DISPLAY {lvds, hdmi}
                        Build image for lvds or hdmi display.
			Default value is 'lvds'

```

To built for Kingfisher with Starter Kit Premiere 8G with DomA (generic yocto-based virtual machine) use the following command line: `moulin prod-cockpit-rcar.yaml --MACHINE h3ulcb-4x2g-kf --ENABLE_ANDROID yes.`

Moulin will generate `build.ninja` file. After that - run `ninja` to build the images. This will take some time and disk space, as it will built 3 separate Yocto images.

This will require even more time and space, as Android is quite big.

## Creating SD card image

Image file can be created with rouge `rouge`. This is a companion application for `moulin`.

It can be invoked either as a standalone tool, or via Ninja.

### Creating image(s) via Ninja

Newer versions of moulin (>= 0.5) will generate two additional Ninja targets:

 - `image-full`
 - `image-android_only` (if building with `--ENABLE_ANDROID=yes`)

Thus, you can just run `ninja image-full` or `ninja full.img` which will generate the `full.img` in your build directory.

Then you can use `dd` to write this image to your SD card. Don't forget `conv=sparse` option for `dd` to speed up writing.

### Using `rouge` in standalone mode

In this mode you can write image right to SD card. But it requires additional options.

In standalone mode`rouge` accepts the same parameters like
`--MACHINE`, `--ENABLE_ANDROID`, `--ENABLE_DOMU` as `moulin` do.

This XT product provides two images: `full` and `android_only`. Latter
is available only when `--ENABLE_ANDROID=yes`.

You can prepare image by running

```
# rouge prod-cockpit-rcar.yaml --ENABLE_ANDROID=yes -i full
```

This will create file `full.img` in your current directory.

Also you can write image directly to a SD card by running

```
# sudo rouge prod-devel-rcar.yaml --ENABLE_DOMU=yes --ENABLE_ANDROID=no -i full -so /dev/sdX
```

**BE SURE TO PROVIDE CORRECT DEVICE NAME**. `rouge` have no
interactive prompts and will overwrite your device right away. **ALL
DATA WILL BE LOST**.

If you want to generate only Android sub-image use `-i android_only`
option.

For more information about `rouge` check its
