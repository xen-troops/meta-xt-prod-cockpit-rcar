
FILESEXTRAPATHS_prepend := "${THISDIR}/qtbase:"

PACKAGECONFIG_GL = "${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'gles2 eglfs', 'no-opengl', d)}"

