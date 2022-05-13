
IMAGE_INSTALL_append = " \
    dual-render-3d-part \
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
"

IMAGE_INSTALL_remove = " \
    dhcp-client \
"
