require qt5-xt-git.inc

SRC_URI:remove = " \
    file://0019-Define-__NR_futex-if-it-does-not-exist.patch \
    file://0020-Revert-Fix-workaround-in-pthread-destructor.patch \
    file://0021-qfloat16-Include-limits-header.patch \
"

SRCREV = "e4961b35deb202525d4711dbb14f8c2bb0bf5c26"
