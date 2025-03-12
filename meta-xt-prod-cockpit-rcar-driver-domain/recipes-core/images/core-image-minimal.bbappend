
IMAGE_INSTALL:append = " \
    xen \
    xen-tools-devd \
    xen-tools-scripts-network \
    xen-tools-scripts-block \
    xen-tools-xenstore \
    xen-network \
    kernel-modules \
    util-linux \
    dnsmasq \
    optee-os \
    fio \
    iotop \
    ca-certificates \
    aos-certificates \
    vis-service \
    cluster-view \
    ${@bb.utils.contains('DISTRO_FEATURES', 'pvcamera', 'camerabe', '', d)} \
"

IMAGE_INSTALL:remove = " \
    dhcp-client \
"

install_aos () {
    if echo "${XT_GUESTS_INSTALL}" | grep -qi "domu";then
        exit 0
    fi
    if [ ! -z "${AOS_VIS_PACKAGE_DIR}" ];then
        opkg install ${AOS_VIS_PACKAGE_DIR}/aos-vis
    fi
}

ROOTFS_POSTPROCESS_COMMAND += "install_aos; "

