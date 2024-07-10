require qt5-xt-git.inc

SRC_URI:remove = " \
    file://0005-Fix-build-with-bison37.patch \
    file://0006-Disable-code-related-to-HTTP-2-when-Qt-is-configured.patch \
    file://0007-Fix-compilation-with-Python-3.9-avoid-passing-encodi.patch \
    file://0008-Fix-build-with-icu-68.patch \
    file://0009-Riscv-Add-support-for-riscv.patch \
"

SRC_URI:append = " \
    file://0005-Riscv-Add-support-for-riscv.patch \
"

SRC_URI:remove:riscv32 = " \
    file://0010-webdriver-libatomic.patch \
"
SRC_URI:remove:riscv64 = " \
    file://0010-webdriver-libatomic.patch \
"

EXTRA_OECMAKE:append:mipsarch = " -DENABLE_JIT=OFF -DENABLE_C_LOOP=ON "
EXTRA_OECMAKE:append:powerpc = " -DENABLE_JIT=OFF -DENABLE_C_LOOP=ON "
EXTRA_OECMAKE:append:riscv64 = " -DENABLE_JIT=OFF -DENABLE_C_LOOP=ON "

EXTRA_OECMAKE:remove:powerpc64le = " \
    -DENABLE_JIT=OFF -DUSE_SYSTEM_MALLOC=ON -DENABLE_C_LOOP=ON \
"

EXTRA_OECMAKE:remove:mipsarch = " \
    -DUSE_LD_GOLD=OFF \
"
EXTRA_OECMAKE:remove:powerpc = " \
    -DUSE_LD_GOLD=OFF \
"
EXTRA_OECMAKE:remove:riscv64 = " \
    -DUSE_LD_GOLD=OFF \
"

EXTRA_OECMAKE:append:toolchain-clang_mipsarch = " \
    -DUSE_LD_GOLD=OFF \
"

