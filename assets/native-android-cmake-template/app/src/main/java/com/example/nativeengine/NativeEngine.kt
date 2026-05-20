package com.example.nativeengine

class NativeEngine {
    external fun processBytes(input: ByteArray): ByteArray

    companion object {
        init {
            System.loadLibrary("native_engine")
        }
    }
}
