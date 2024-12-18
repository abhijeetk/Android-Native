/*
These three pages were instrumental while trying to get this working.
I started with existing examples, got them working, and updated
them to make sure I undersood how things worked. If you are trying this
for the first time, I suggest adding a new method with different arguments
to the Java class and then calling it from this C program.
Use 'javap -s -p helloWorld.class' to get the new method signature.
After that is working, package the class in a jar file, update the class
path in this C source file, and get that working.
http://www.inonit.com/cygwin/jni/invocationApi/c.html
http://www.codeproject.com/Articles/22881/How-to-Call-Java-Functions-from-C-Using-JNI
http://java.sun.com/developer/onlineTraining/Programming/JDCBook/jniexamp.html
*/


#include <stdio.h>
#include <jni.h>
#include <nativehelper/JniInvocation.h>

JNIEnv* create_vm()
{
    const char* lib = "libart.so"; // or another appropriate runtime library for your system

    // Initialize the JNI invocation system
    JniInvocation jni_invocation;
    if (!jni_invocation.Init(lib)) {
        fprintf(stderr, "Failed to initialize JNI invocation API from %s\n", lib);
        return nullptr;
    }

    JavaVM* vm = nullptr;
    JNIEnv* env = nullptr;

    JavaVMOption options[2];
    options[0].optionString = "-Djava.class.path=/data/local/tmp/helloWorld.jar";
    options[1].optionString = "-verbose:class";

    JavaVMInitArgs init_args;
    init_args.version = JNI_VERSION_1_6;
    init_args.nOptions = 2;
    init_args.options = options;
    init_args.ignoreUnrecognized = 0;

    int rv;

    rv = JNI_CreateJavaVM(&vm, &env, &init_args);

    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n",rv);
    else
        printf("Launched JVM! :)\n");
    return env;
}

void invoke_class(JNIEnv* env)
{
    jclass hello_world_class;
    jmethodID main_method;
    jmethodID square_method;
    jmethodID power_method;
    jint number=20;
    jint exponent=3;
    hello_world_class = env->FindClass("helloWorld");
    main_method = env->GetStaticMethodID(hello_world_class, "main", "([Ljava/lang/String;)V");
    square_method = env->GetStaticMethodID(hello_world_class, "square", "(I)I");
    power_method = env->GetStaticMethodID(hello_world_class, "power", "(II)I");
    env->CallStaticVoidMethod(hello_world_class, main_method, nullptr);
    printf("%d squared is %d\n", number,
        env->CallStaticIntMethod(hello_world_class, square_method, number));
    printf("%d raised to the %d power is %d\n", number, exponent,
        env->CallStaticIntMethod(hello_world_class, power_method, number, exponent));
}

int main(int argc, char **argv)
{
    JNIEnv *env = create_vm();
    if(env == nullptr)
        return 1;
    invoke_class(env);
    return 0;
}

