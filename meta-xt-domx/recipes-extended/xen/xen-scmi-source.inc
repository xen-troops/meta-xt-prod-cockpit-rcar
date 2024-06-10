FILESEXTRAPATHS_append := "${THISDIR}/files:"

XEN_URL_append= " \
	file://0003-xen-hypfs-support-fo-nested-dynamic-hypfs-nodes.patch \
	file://0004-libs-libxenhypfs-handle-blob-properties.patch \
	file://0005-xen-arm-Export-host-device-tree-to-hypfs.patch \
	file://0006-xen-arm-add-generic-SCI-mediator-framework.patch \
	file://0007-xen-arm-introduce-SCMI-SMC-mediator-driver.patch \
	file://0008-tools-arm-Introduce-force_assign_without_iommu-optio.patch \
	file://0009-tools-arm-add-arm_sci-option-to-xl.cfg.patch \
	file://0010-xen-arm-add-SCI-mediator-support-for-DomUs.patch \
	file://0011-dt_find_node_by_phandle-move-the-function-in-public-.patch \
	file://0012-domain.c-Remove-the-initialization-of-sci-for-idle_d.patch \
	file://0013-domain_create-use-arch_domain_create-after-rangeset-.patch \
	file://0014-iommu-iommu_do_domctl-change-initial-ret-value.patch \
	file://0015-xt_defconfig-add-scmi-to-the-build.patch \
	file://0016-domain-Dom0-call-the-sci_domain_init-once.patch \
	file://0017-aquire_scmi_channel-code-optimization.patch \
	file://0018-rcar3.c-introduce-the-communication-protocol-with.patch \
"

