package com.example.nativeimage

class NativeImageProcessor {
    external fun invertRgba(
        rgba: ByteArray,
        width: Int,
        height: Int,
        strideBytes: Int
    ): ByteArray

    companion object {
        init {
            System.loadLibrary("native_image_processor")
        }
    }
}
