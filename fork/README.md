# Goal
To check if fork and exec works as expected on android native. When we tried to use fork/exec in NativeActivity
it did not work.

> Abort message: 'Error changing dalvik-cache ownership : Permission denied'

Only ROOT user has permission to `/data/dalvik-cache`. You can refer Android open source code which triggeres this error here.

```
   result = chown(dalvikCacheDir, AID_ROOT, AID_ROOT);
    LOG_ALWAYS_FATAL_IF((result < 0), "Error changing dalvik-cache ownership : %s", strerror(errno));
```

https://android.googlesource.com/platform/frameworks/base.git/+/master/cmds/app_process/app_main.cpp

## Build
in aosp root directory run 
```
export OUT_DIR=out_arm64
source build/envsetup.sh
lunch aosp_cf_arm64_phone-trunk_staging-userdebug
m fork_native
```
It will generate `out_arm64/target/product/vsoc_arm64/system/bin/fork_native`.

Push it to device/emulator to /data/local/tmp/

## Push jar and executable to device
```
adb push out_arm64/target/product/vsoc_arm64/system/bin/fork_native /data/local/tmp
```

## Run
```
adb shell

m14x:/data/local/tmp $ ./fork_native
```
## Debug
Run logcat in another terminal before running ./hello_world_native
```
adb logcat 
```

