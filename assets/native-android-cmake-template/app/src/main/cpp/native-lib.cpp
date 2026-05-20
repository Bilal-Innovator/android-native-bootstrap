#include <jni.h>

#include <cstdint>
#include <vector>

#include "image_processor.h"

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_nativeimage_NativeImageProcessor_invertRgba(
    JNIEnv* env,
    jobject,
    jbyteArray rgba,
    jint width,
    jint height,
    jint strideBytes
) {
    if (rgba == nullptr || width <= 0 || height <= 0 || strideBytes <= 0) {
        return env->NewByteArray(0);
    }

    const jsize input_size = env->GetArrayLength(rgba);
    std::vector<std::uint8_t> input(static_cast<std::size_t>(input_size));
    env->GetByteArrayRegion(
        rgba,
        0,
        input_size,
        reinterpret_cast<jbyte*>(input.data())
    );

    std::vector<std::uint8_t> output = nativeimage::invert_rgba(
        input.data(),
        width,
        height,
        strideBytes
    );

    jbyteArray result = env->NewByteArray(static_cast<jsize>(output.size()));
    if (result == nullptr || output.empty()) {
        return result;
    }

    env->SetByteArrayRegion(
        result,
        0,
        static_cast<jsize>(output.size()),
        reinterpret_cast<const jbyte*>(output.data())
    );
    return result;
}
