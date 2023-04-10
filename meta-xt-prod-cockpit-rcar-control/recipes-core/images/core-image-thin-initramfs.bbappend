IMAGE_INSTALL_append = " xen-tools-xenstat"
IMAGE_INSTALL_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'pvcamera', 'camera-hotplug', '', d)}"
