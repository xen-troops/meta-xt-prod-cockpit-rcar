require qt5-xt-git.inc

PACKAGECONFI:remove = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'opengl wayland', 'wayland-egl', '', d)} \
"

PACKAGECONFIG += " \
   ${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'wayland-egl', '', d)} \
"

SRCREV = "c25f8b8fa4dc6d096382d34849b997ab7fe69c5c"

PACKAGECONFIG[wayland-layer-integration-vsp2] = "-feature-wayland-layer-integration-vsp2,-no-feature-wayland-layer-integration-vsp2"
PACKAGECONFIG += " wayland-server wayland-layer-integration-vsp2 "

