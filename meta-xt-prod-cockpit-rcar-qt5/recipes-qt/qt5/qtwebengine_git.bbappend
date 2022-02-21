require qt5-xt-git.inc

DEPENDS_remove = " \
    dbus \
    nodejs-native \
    libxkbcommon \
    jpeg-native \
    freetype-native \
"

DEPENDS += " \
    icu \
"

PACKAGECONFIG += " \
    libwebp \
"

PACKAGECONFIG[protobuf] = "-feature-webengine-system-protobuf,-no-feature-webengine-system-protobuf,protobuf"
PACKAGECONFIG[jsoncpp] = "-feature-webengine-system-jsoncpp,-no-feature-webengine-system-jsoncpp,jsoncpp"

QT_MODULE_BRANCH_CHROMIUM = "80-based"

SRC_URI_remove = " \
    file://0002-qmake.conf-lower-MODULE_VERSION-to-5.15.2.patch \
"

SRC_URI_remove_libc-musl = " \
    file://0003-musl-don-t-use-pvalloc-as-it-s-not-available-on-musl.patch \
    file://0004-musl-link-against-libexecinfo.patch \
    file://0005-mkspecs-Allow-builds-with-libc-glibc.patch \
"

SRC_URI_append_libc-musl = " \
    file://0002-musl-don-t-use-pvalloc-as-it-s-not-available-on-musl.patch \
    file://0003-musl-link-against-libexecinfo.patch \
    file://0004-mkspecs-Allow-builds-with-libc-glibc.patch \
"

SRC_URI_remove_libc-musl = " \
    file://chromium/0012-chromium-musl-sandbox-Define-TEMP_FAILURE_RETRY-if-n.patch;patchdir=src/3rdparty \
    file://chromium/0013-chromium-musl-Avoid-mallinfo-APIs-on-non-glibc-linux.patch;patchdir=src/3rdparty \
    file://chromium/0014-chromium-musl-include-fcntl.h-for-loff_t.patch;patchdir=src/3rdparty \
    file://chromium/0015-chromium-musl-use-off64_t-instead-of-the-internal-__.patch;patchdir=src/3rdparty \
    file://chromium/0016-chromium-musl-linux-glibc-make-the-distinction.patch;patchdir=src/3rdparty \
    file://chromium/0017-chromium-musl-Define-res_ninit-and-res_nclose-for-no.patch;patchdir=src/3rdparty \
    file://chromium/0018-chromium-musl-Do-not-define-__sbrk-on-musl.patch;patchdir=src/3rdparty \
    file://chromium/0019-chromium-musl-Adjust-default-pthread-stack-size.patch;patchdir=src/3rdparty \
    file://chromium/0020-chromium-musl-elf_reader.cc-include-sys-reg.h-to-get.patch;patchdir=src/3rdparty \
    file://chromium/0021-chromium-musl-pread-pwrite.patch;patchdir=src/3rdparty \
    file://chromium/0022-chromium-musl-initialize-msghdr-in-a-compatible-mann.patch;patchdir=src/3rdparty \
"

SRC_URI_append_libc-musl = " \
    file://chromium/0013-chromium-musl-sandbox-Define-TEMP_FAILURE_RETRY-if-n.patch;patchdir=src/3rdparty \
    file://chromium/0014-chromium-musl-Avoid-mallinfo-APIs-on-non-glibc-linux.patch;patchdir=src/3rdparty \
    file://chromium/0015-chromium-musl-include-fcntl.h-for-loff_t.patch;patchdir=src/3rdparty \
    file://chromium/0016-chromium-musl-use-off64_t-instead-of-the-internal-__.patch;patchdir=src/3rdparty \
    file://chromium/0017-chromium-musl-linux-glibc-make-the-distinction.patch;patchdir=src/3rdparty \
    file://chromium/0018-chromium-musl-allocator-Do-not-include-glibc_weak_sy.patch;patchdir=src/3rdparty \
    file://chromium/0019-chromium-musl-Use-correct-member-name-__si_fields-fr.patch;patchdir=src/3rdparty \
    file://chromium/0020-chromium-musl-Define-res_ninit-and-res_nclose-for-no.patch;patchdir=src/3rdparty \
    file://chromium/0021-chromium-musl-Do-not-define-__sbrk-on-musl.patch;patchdir=src/3rdparty \
    file://chromium/0022-chromium-musl-Adjust-default-pthread-stack-size.patch;patchdir=src/3rdparty \
    file://chromium/0023-chromium-musl-Use-_fpstate-instead-of-_libc_fpstate-.patch;patchdir=src/3rdparty \
    file://chromium/0024-chromium-musl-elf_reader.cc-include-sys-reg.h-to-get.patch;patchdir=src/3rdparty \
    file://chromium/0025-chromium-musl-pread-pwrite.patch;patchdir=src/3rdparty \
    file://chromium/0026-chromium-musl-initialize-msghdr-in-a-compatible-mann.patch;patchdir=src/3rdparty \
"

SRCREV_qtwebengine = "9e4d1eb45d5c6299e79ac3f28282fd76f949980e"
SRCREV_chromium = "62bc475876cbae17e2e39175fe321780512e5951"

