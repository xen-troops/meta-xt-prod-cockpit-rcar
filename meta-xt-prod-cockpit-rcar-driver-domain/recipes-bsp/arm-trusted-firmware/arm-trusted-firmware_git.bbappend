FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# This patch is required for CR7 on M3. Received from Renesas.
SRC_URI_r8a7796_append = "\
    file://0001-Enable-DAVEHD-on-R-Car-M3.patch \
"

# These patches are required for CR7 on H3/M3 boards. Received from Renesas.
SRC_URI_append = "\
    file://0002-Change-the-security-attribute-setting-for-Cortex-R7.patch \
    file://0003-Kick_CR7_in_bl2.patch \
"
