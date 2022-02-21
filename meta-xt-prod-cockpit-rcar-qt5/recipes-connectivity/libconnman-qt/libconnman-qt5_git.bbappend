PV = "1.2.7+git${SRCPV}"

SRCREV = "ad7fef1c35a3e897913965f73b879a14d65043dd"

SRC_URI_remove = " \
    file://0001-Add-missing-declarations-for-operator-overloads.patch \
"

SRC_URI_append = " \
    file://0001-Fix-library-path-for-multilib-setups.patch \
"
