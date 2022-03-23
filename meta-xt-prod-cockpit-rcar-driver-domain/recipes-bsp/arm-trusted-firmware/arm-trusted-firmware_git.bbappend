FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

ATFW_OPT_RPC = "${@oe.utils.conditional("DISABLE_RPC_ACCESS", "1", " RCAR_RPC_HYPERFLASH_LOCKED=1", "RCAR_RPC_HYPERFLASH_LOCKED=0", d)}"
ADDITIONAL_ATFW_OPT_append = " ${ATFW_OPT_RPC} RCAR_BL33_EXECUTION_EL=1"
ADDITIONAL_ATFW_OPT ??= ""

SRC_URI_append = " \
    file://0004-Enable-DAVEHD-on-R-Car-M3.patch \
    file://0005-Change-the-security-attribute-setting-for-Cortex-R7-.patch \
    file://0006-Kick-CR7-in-bl2.patch \
    file://0008-ATF-Add-additional-registers-logs.patch \
"

do_compile() {
    oe_runmake distclean
    oe_runmake bl2 bl31 rcar_layout_tool rcar_srecord PLAT=${PLATFORM} SPD=opteed MBEDTLS_COMMON_MK=1 ${ATFW_OPT} ${ADDITIONAL_ATFW_OPT}
}

# Override the do_ipl_opt_compile function to add the ${ATFW_OPT_RPC} option
do_ipl_opt_compile () {
    oe_runmake distclean
    oe_runmake bl2 bl31 rcar_layout_tool rcar_srecord PLAT=${PLATFORM} SPD=opteed MBEDTLS_COMMON_MK=1 ${EXTRA_ATFW_OPT} ${ATFW_OPT_LOSSY} ${ATFW_OPT_RPC} ${ADDITIONAL_ATFW_OPT}
}

# For IPL compile options for H3/H3ULCB (SoC: r8a7795), E3 (SoC: r8a7790)
python do_extra_ipl_opt () {
    soc = d.getVar('SOC_FAMILY')
    soc = soc.split(':')[1]
    machine = d.getVar('MACHINE_ARCH')

    if soc == "r8a7795":
        if "h3ulcb" not in machine:
            do_extra_aft_build(d, "H3")
        else:
            do_extra_aft_build(d, "H3ULCB")

    if soc == "r8a77990":
        do_extra_aft_build(d, "E3")
}

