SRC_URI_append = " \
    file://0001-rcar-create-rcar3-platform-file.patch \
    file://0002-arm-platform-add-late_init-callback.patch \
    file://0003-rcar3-add-support-for-MFIS-driver.patch \
    file://0004-rcar3-add-pv-rproc-support.patch \
    file://0005-xen-arm-introduce-p2m_is_mmio.patch \
    file://0006-xen-extend-XEN_DOMCTL_memory_mapping-to-handle-memor.patch \
    file://0007-libxc-introduce-xc_domain_mem_map_policy.patch \
    file://0008-libxl-xl-add-memory-policy-option-to-iomem.patch \
    file://0009-xen-arm-clarify-the-support-status-of-iomem-configur.patch \
    file://0010-domctl-add-enable_rproc-domctl.patch \
    file://0011-platform-add-ability-to-provide-platform-specific-do.patch \
    file://0012-rcar3-move-MFIS-SPI-IRQ-number-definition-to-public-.patch \
    file://0013-rcar3-add-domctl-handler.patch \
    file://0014-tools-xc-add-xc_domain_setrproc-function.patch \
    file://0015-tools-xl-add-rproc-option.patch \
    file://0016-rcar3-do-not-enable-MFIS-and-rproc-for-Dom0.patch \
    file://0017-xen-arm-Introduce-platform_domain_destroy-and-corres.patch \
    file://0018-xsm-add-Flask-policy-for-enable_rproc.patch \
    file://0019-destroy_domain-add-verification-of-NULL-to-avoid-the.patch \
    file://0020-rcar3.c-introduce-the-communication-protocol-with-cl.patch \
    file://0021-xt_defconfig-add-scmi-support.patch \
    file://0022-xen-common-domctl.c-fix-commit-from-Stefano-put-it-i.patch \
    file://0023-xsm-add-Flask-policy-for-get_sci_info.patch \
    file://0024-hooks.c-add-XEN_DOMCTL_get_sci_info.patch \
"
