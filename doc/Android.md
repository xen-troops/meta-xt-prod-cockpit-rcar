## How to rebuild Android & Android Kernel with some changes

Imagine the root of the work directory looks like this:

```
$WORKDIR
├── android
├── android_kernel
├── build.ninja
├── docker
├── prod-cockpit-rcar.yaml
└── yocto
```

## Rebuilding Android Kernel manually

```
pushd android_kernel

TARGET_BOARD_PLATFORM=r8a7795 BUILD_CONFIG=common/build.config.xenvm SKIP_MRPROPER=1 build/build.sh

popd
```

If you want clean rebuild opt-out SKIP_MRPROPER=1
All artifacts will be in : `android_kernel/out/android12-5.4/dist`

Or you may use `ninja doma_kernel` from the $WORKDIR

## Rebuild Android

If you rebuilt the Android kernel, it should be sufficient to execute `ninja doma`  from $WORKDIR to include updated artifacts to Android images.

In case you updated some sources inside Android, moulin may not notice it, since it tracks output artifacts state (`android/out/target/product/xenvm/*.img`) which might be present, and `ninja doma` may not trigger Android build system.

In that case, you need to trigger the Android build system manually to update images:

```
pushd android

export TARGET_BOARD_PLATFORM=r8a7795 TARGET_PREBUILT_KERNEL=../android_kernel/out/android12-5.4/dist/Image DDK_KM_PREBUILT_MODULE=../android_kernel/out/android12-5.4/dist/pvrsrvkm.ko KERNEL_MODULES_OUT=../android_kernel/out/android12-5.4/dist

. ./build/envsetup.sh

lunch xenvm-userdebug

m

popd
```