#include <jni.h>

#include <cstdint>
#include <vector>

#include "native_engine.h"

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_nativeengine_NativeEngine_processBytes(
    JNIEnv* env,
    jobject,
    jbyteArray inputBytes
) {
    if (inputBytes == nullptr) {
        return env->NewByteArray(0);
    }

    const jsize input_size = env->GetArrayLength(inputBytes);
    std::vector<std::uint8_t> input(static_cast<std::size_t>(input_size));
    env->GetByteArrayRegion(
        inputBytes,
        0,
        input_size,
        reinterpret_cast<jbyte*>(input.data())
    );

    std::vector<std::uint8_t> output = nativeengine::process_bytes(
        input.data(),
        input_size
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
