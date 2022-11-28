FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# This patch is required for CR7 on M3. Received from Renesas.
SRC_URI_r8a7796_append = "\
    file://0001-Enable-DAVEHD-on-R-Car-M3.patch \
"

# These patches are required for CR7 on H3/M3 boards. Received from Renesas.
SRC_URI_append = "\
    file://0002-Change-the-security-attribute-setting-for-Cortex-R7.patch \
    file://0003-Kick_CR7_in_bl2.patch \
    file://0003-Add-bldcmd.sh.patch \
    file://0005-rcar-Add-DRAM2_NS_SCMI-memory-region-to-BL31-mapping.patch \
    file://0006-rcar-add-SCMI-reset-protocol-implementation.patch \
    file://0007-rcar-add-SCMI-clock-protocol-implementation.patch \
    file://0008-rcar-add-SCMI-stub-power-protocol-implementation.patch \
    file://0008-sip_sv-rollback-the-service-to-support-scmi.patch \
    file://0009-rcar-SCMI-base-protocol-implementation-and-handling.patch \
    file://0010-rcar-scmi-add-physical-resources-to-SCMI-devices.patch \
    file://0011-bldcmd.sh-build-scmi-platform-by-default.patch \
    file://0001-rcar_scmi_clocks.c-fix-build-error-no-returned-value.patch \
"

# This patch is required for CR7 on H3. Strictly speaking it is needed only
# for Kingfisher board, but since prod-cockpit supports only a single board
# put it here.
SRC_URI_append_r8a7795 = "\
    file://0001-pfc-h3-Configure-DU_DISP-pin.patch \
"
