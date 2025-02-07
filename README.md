# meta-xt-prod-cockpit-rcar

- [Software preparation](#software-preparation)
  - [git](#git)
  - [serial port tools](#serial-port-tools)
  - [docker](#docker)
  - [prebuilt binaries](#prebuilt-binaries)
  - [ssh](#ssh)
  - [open ports](#open-ports)
  - [TFTP server](#tftp-server)
  - [NFS server](#nfs-server)
- [Build the product](#build-the-product)
  - [prebuilt gsx](#prebuilt-gsx)
  - [building](#building)
  - [known issues](#known-issues)
- [Flash the board](#flash-the-board)
  - [loaders](#loaders)
  - [u-boot env](#u-boot-env)
  - [cluster firmware](#cluster-firmware)
  - [image](#image)


## Software preparation
This product uses proprietary sources and binaries.
Please contact us to request the access to the following repo:
- https://gitpct.epam.com/rec-inv
- https://gitpct.epam.com/epmp-aos

### git
Install `git` and create `~/.gitconfig` file
```
sudo apt install git
git config --global user.name "your name"
git config --global user.email "your e-mail"
```

### serial port tools
Install `pyftdi` according to https://eblot.github.io/pyftdi/installation.html

```
sudo apt install python3-serial
sudo apt install minicom
sudo usermod -aG dialout $USER
```

Set up minicom
```
sudo minicom -s
```
Select "Serial port setup" and provide:
- port connected to the board - /dev/ttyUSB0
- Bps/Par/Bits - 115200 8N1
- Hardware/Software Flow Control - No

Press Enter and select "Save setup as dfl".

### docker
```
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```
If you have any issues with installation, please use the
[manual](https://docs.docker.com/engine/install/ubuntu/).

Add yourself to the docker group to run it without `sudo`:
```
sudo groupadd docker
sudo usermod -aG docker $USER
```
Log out and log in again to properly apply the new group.
Use the [manual](https://docs.docker.com/engine/install/linux-postinstall/)
in case of any issue.

Create the build container
```
curl -O https://raw.githubusercontent.com/xen-troops/meta-xt-prod-cockpit-rcar/master/doc/Dockerfile
docker build . -f Dockerfile --build-arg "USER_ID=$(id -u)" --build-arg "USER_GID=$(id -g)" -t u20:latest
```

### prebuilt binaries
Download three archives with the prebuilt graphics from
https://gitbud.epam.com/epmp-aos/kf_prebuilt_graphics

Download `nfs.tar.bz2` and `tftp.tar.bz2` from
https://gitbud.epam.com/epmp-aos/kf_nfs_and_tftp_data.

### ssh
Add your public key on the page https://github.com/settings/keys.
If you do not have ssh key or need any help, follow the
[manual](https://docs.github.com/en/authentication/connecting-to-github-with-ssh).

Go to https://gitpct.epam.com/-/user_settings/ssh_keys and add
the same public key. Follow the [instructions](https://gitpct.epam.com/help/user/ssh)
if needed.

Repeat for the https://gitbud.epam.com/-/user_settings/ssh_keys.

Add sites to the list of known hosts.
Type `yes` when asked by the following commands:
```
ssh github.com
ssh gitpct.epam.com
ssh gitpct.epam.com
```

### open ports
If you have a firewall, you should unblock all ports on the network interface
connected to the board. For example, allow anything on the interface `eth2`
```
sudo ufw allow in on eth2
sudo ufw allow out on eth2
```

### TFTP server
Install server and unpack BSP's kernel and device tree from already
downloaded `tftp.tar.bz2`.
```
sudo apt-get install tftp tftpd-hpa
tar -xjf <downloads>/tftp.tar.bz2 -C /srv/tftp
```

### NFS server
Install and unpack BSP's rootfs from already downloaded `nfs.tar.bz2`
```
sudo apt-get install nfs-kernel-server nfs-common
sudo /etc/init.d/nfs-kernel-server start
tar -xjf <downloads>/nfs.tar.bz2 -C /srv/nfs
```
Add the following line to the `/etc/exports` file:
```
/srv/nfs	*(rw,no_subtree_check,sync,no_root_squash,no_all_squash)
```
Update info for the NFS server
```
sudo exportfs -a
```



## Build the product

Create some work directory and download yaml-file and script to it. We will use
`${WORK_DIR}` as the reference to the work directory in the next steps.
```
export WORK_DIR=<provide some path>
mkdir -p ${WORK_DIR}
cd ${WORK_DIR}
curl -O https://raw.githubusercontent.com/xen-troops/meta-xt-prod-cockpit-rcar/refs/heads/master/prod-cockpit-rcar.yaml
curl -O https://raw.githubusercontent.com/xen-troops/meta-xt-prod-cockpit-rcar/refs/heads/master/doc/run_docker.sh
```

### prebuilt gsx
Put already downloaded prebuilt binaries
```
mkdir -p ${WORK_DIR}/prebuilt_gsx/domd
cp <downloads>/r8a77951_linux_gsx_binaries_gles.tar.bz2 ${WORK_DIR}/prebuilt_gsx/domd
cp <downloads>/GSX_KM_H3.tar.bz2 ${WORK_DIR}/prebuilt_gsx/domd
cp <downloads>/rcar-prebuilts-graphics-xt-doma.tar.gz ${WORK_DIR}
```

### building
Start the build container and run the build
```
./run_docker.sh -w ${WORK_DIR} -d u20
moulin prod-cockpit-rcar.yaml --PREBUILT_DDK yes --ENABLE_CLUSTER yes --ENABLE_ANDROID yes --ENABLE_TOOLS yes --ANDROID_PREBUILT_DDK yes
ninja full.img
```
The build takes 5 to 10 hours, depending on network and host capabilities.

### known issues
Sometimes, we may observe fetch errors due to network or server-side limitations.
Just repeat `ninja full.img`.

Also, sometimes, the build of the Android may hang after a successful build.
You will see `#### build completed successfully (__:__ (mm:ss)) ####` message
hanging for some time and nothing happens.
In this case, you need to abort the build (Ctrl+C) and restart `ninja full.img`.



## Flash the board

### loaders
We use [rcar_flash](https://github.com/xen-troops/rcar_flash) for flashing loaders.
Get the tool into some folder.
```
git clone https://github.com/xen-troops/rcar_flash.git
```
Turn on your board and run the following command
```
sudo ./rcar_flash.py flash -c -f -b h3ulcb_4x2 -s /dev/ttyUSB0 -p ${WORK_DIR}/yocto/build-domd/tmp/deploy/images/h3ulcb/firmware all
```

### u-boot env
Start `minicom` on the host.
Reboot the board and press any key to stop u-boot.

Set MAC address according to the sticker on the Ethernet connector
```
setenv ethaddr __:__:__:__:__:__
```

Set commands required for the proper work of the u-boot
```
setenv bootargs
setenv ipaddr 192.168.5.22
setenv serverip 192.168.5.75
setenv initrd_high 0xffffffffffffffff
setenv bootcmd run bootcmd_emmc
setenv bootcmd_emmc 'run emmc_xen_load; run emmc_dtb_load; run emmc_kernel_load; run emmc_xenpolicy_load; run emmc_initramfs_load; bootm 0x48080000 0x84000000 0x48000000'
setenv emmc_dtb_load 'ext2load mmc 1:1 0x48000000 xen.dtb; fdt addr 0x48000000; fdt resize; fdt mknode / boot_dev; fdt set /boot_dev device mmcblk0'
setenv emmc_initramfs_load ext2load mmc 1:1 0x84000000 uInitramfs
setenv emmc_kernel_load ext2load mmc 1:1 0x8a000000 Image
setenv emmc_xen_load ext2load mmc 1:1 0x48080000 xen
setenv emmc_xenpolicy_load ext2load mmc 1:1 0x8c000000 xenpolicy

setenv bootcmd_bsp 'run bsp_set_args; run bsp_cmd'
setenv bsp_cmd 'tftp 0x48080000 Image; tftp 0x48000000 r8a77951-ulcb-kf.dtb; booti 0x48080000 - 0x48000000'
setenv bsp_set_args 'setenv bootargs ignore_loglevel clk_ignore_unused=1 rw root=/dev/nfs nfsroot=/srv/nfs,nfsvers=3 ip=${ipaddr}:${serverip}::255.255.255.0'

saveenv flash_cluster 'tftp 0x48000000 cluster_wrapper.bin; erase 0x0A000000 +0x${filesize}; cp.b 0x48000000 0x0A000000 0x${filesize}'

saveenv
```

### cluster firmware
Copy the cluster binary to TFTP folder
```
sudo cp ${WORK_DIR}/yocto/build-cluster-wrapper/tmp/deploy/cluster_wrapper.bin /srv/tftp
```
On the board, in the u-boot, run the command
```
==> run flash_cluster
```

### image
Put `full.img` to the NFS root
```
cp ${WORK_DIR}/full.img /srv/nfs
```
In the u-boot, start BSP
```
==> run bootcmd_bsp
```
Login as `root` and flash the `full.img` to the eMMC
```
dd if=/full.img of=/dev/mmcblk0 status=progress oflag=direct
```

After reboot, the board will start loading xen with all domains from the eMMC.
The demo is installed and ready for work.

