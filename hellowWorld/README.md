# Calling Java Class Methods from C++ with JNI
This repository ports sample specified in https://www.hildstrom.com/projects/2012/10/jni/index.html on AOSP.
Main aim of this project is to check feasibility if we can call Java from C++ code without beign part of android APK.

## Clone https://github.com/abhijeetk/Android-Native/tree/main/helloWorld to aosp/external
```
/aosp/external  $ tree helloWorld/
hellowWorld/
├── Android.bp
├── helloWorld.java
└── native
    ├── Android.bp
    ├── hello_world.c
    └── README
```

## Build
in aosp root directory run 
```
export OUT_DIR=out_arm64
source build/envsetup.sh
lunch aosp_cf_arm64_phone-trunk_staging-userdebug
m hello_world_java hello_world_native
```
It will generate ./out_arm64/target/product/vsoc_arm64/system/framework/helloWorld.jar and
out_arm64/target/product/vsoc_arm64/system/bin/hello_world_native
Push it to device/emulator to /data/local/tmp/

## Push jar and executable to device
```
adb push out_arm64/target/product/vsoc_arm64/system/bin/hello_world_native /data/local/tmp
adb push out_arm64/target/product/vsoc_arm64/system/framework/helloWorld.jar /data/local/tmp/
```

## Run
```
adb shell
m14x:/data/local/tmp $ ./hello_world_native                                                                   
Launched JVM! :)
Hello, World
20 squared is 400
20 raised to the 3 power is 8000
```


