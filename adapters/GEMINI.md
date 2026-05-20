# Android Native Bootstrap Adapter

Follow `android-native-bootstrap/SKILL.md` for Android JNI, CMake, NDK, ABI, and native C++ engine work.

Prefer the official Android CLI workflow first for Android project creation, project inspection, SDK management, documentation lookup, and deployment. Use this custom skill only when Android CLI support is insufficient for JNI boundaries, CMake target layout, NDK pinning, ABI filters, shared native runtimes, reusable native C++ core modules, or performance-critical native layers.

Reuse existing Gradle, CMake, and JNI configuration when it is coherent. Patch incrementally. Avoid duplicate bootstrap logic, unnecessary CLI executions, broad dependency upgrades, and full project regeneration.

When native templates are needed, use:

```text
android-native-bootstrap/assets/native-android-cmake-template/
```
