---
name: android-native-bootstrap
description: Deterministic bootstrap and repair protocol for native Android projects that use Kotlin/Java plus a native C++ core module through JNI, CMake, NDK, Gradle, and ABI configuration. Use when creating, recreating, repairing, or extending Android projects with native-lib.cpp, CMakeLists.txt, externalNativeBuild, abiFilters, Android CLI for agents, Android NDK, JNI bridges, high-performance native engines, shared native runtimes, reusable C++ modules, or token-efficient Android native scaffolding.
---

# Android Native Bootstrap

## Core Rules

1. **Android CLI first**: Use official Android CLI workflows for project creation, project inspection, SDK management, docs lookup, deployment, and Android CLI skill commands.
2. **Native overlay only**: Use this skill only where Android CLI or the existing project is insufficient for JNI, CMake, NDK, ABI filters, or native C++ core structure.
3. **Strict native boundary**: `app/src/main/cpp/core/` must stay pure standard C++ with zero `jni.h` or Android dependencies. JNI belongs only in `app/src/main/cpp/native-lib.cpp`.
4. **Incremental diffs**: Reuse coherent Gradle, CMake, JNI, Kotlin, and Java files. Patch minimally; do not rewrite working files to match the template.
5. **No speculation**: Do not upgrade AGP, Gradle, Kotlin, SDK, NDK, CMake, Compose, or dependencies unless the user asks, Android CLI requires it, or a verified build failure requires it.
6. **Run commands once**: Do not repeat discovery commands in the same task unless files or installed tools changed.

## Required Prerequisite

Android CLI must be installed before using Android CLI workflows.

Preflight:

```bash
android info
```

If `android` is missing, stop and ask the user to install Android CLI from the official download page:

```text
https://developer.android.com/tools/agents/android-cli/download
```

Windows:

```powershell
winget install --id Google.AndroidCLI
```

Use bundled templates offline only when the user explicitly allows continuing without Android CLI.

## Command Selector

Run the narrowest command that answers the current question:

| Need | Command |
| --- | --- |
| Verify Android CLI | `android info` |
| Check Android CLI skills | `android skills list` |
| Add official Android CLI skill | `android skills add android-cli` |
| Inspect existing project | `android describe --project_dir=<project-root>` |
| Inspect create syntax | `android create -h` |
| List templates | `android create --list` or installed CLI equivalent |
| Create official app shell | `android create --name=<app-name> -o=<dest> <template>` |
| Lookup docs | `android docs search "<topic>"` |
| Inspect SDK packages | `android sdk list "ndk|cmake|platforms|build-tools"` |

Follow installed CLI help over remembered syntax. Some Android CLI versions use `android create --list`; others document `android create list`.

## Workflow

1. Inspect the environment with `android info`.
2. For existing projects, read `settings.gradle*`, root `build.gradle*`, module `build.gradle*`, `CMakeLists.txt`, and JNI files before editing.
3. For new projects, create the Android shell with Android CLI.
4. Overlay files from `assets/native-android-cmake-template/` only if native C++ support is missing.
5. Patch package names, namespace, app id, SDK values, ABI list, and JNI symbols only when required.
6. Validate incrementally.

## Standard Native Shape

Use this shape only when creating or repairing missing native structure:

```text
<root>/
  settings.gradle.kts
  build.gradle.kts
  gradle/libs.versions.toml
  app/
    build.gradle.kts
    src/main/
      AndroidManifest.xml
      java/<package>/NativeEngine.kt
      cpp/
        CMakeLists.txt
        native-lib.cpp
        core/
          native_engine.h
          native_engine.cpp
```

Template files live in:

```text
assets/native-android-cmake-template/
```

## Gradle, CMake, And NDK Guardrails

- Keep `externalNativeBuild.cmake.path` pointed at `src/main/cpp/CMakeLists.txt`.
- Pin `ndkVersion` only when creating a new native setup or fixing NDK drift.
- Pin ABI filters in one place:

```kotlin
ndk {
    abiFilters += listOf("arm64-v8a", "armeabi-v7a", "x86_64")
}
```

- Keep C++ flags narrow: `-std=c++17 -fexceptions -frtti`.
- Keep CMake target name deterministic for new templates: `native_engine`.
- Prefer version catalogs for new explicit dependency versions.
- Load `references/cutting-edge-android.md` only for explicit latest/cutting-edge requests.

## JNI Guardrails

- Keep JNI methods small: validate inputs, translate data, call the C++ core, translate results.
- Use standard region methods such as `GetByteArrayRegion` and `SetByteArrayRegion` for simple array bridges.
- Do not duplicate custom buffer helpers across files.
- Keep reusable logic in `core/` so it can be shared outside Android.
- Use deterministic names for new templates:
  - Kotlin/Java facade: `NativeEngine`
  - JNI bridge: `native-lib.cpp`
  - CMake library target: `native_engine`

## Validation Ladder

Run the narrowest useful check:

```bash
android describe --project_dir=<project-root>
./gradlew :app:tasks
./gradlew :app:externalNativeBuildDebug
./gradlew :app:assembleDebug
android run --apks=<apk-path>
```

On Windows, use `.\gradlew.bat` when present. If `externalNativeBuildDebug` is unavailable, inspect `.\gradlew.bat :app:tasks --all` and use the closest generated native build task.

## Failure Handling

- CMake cannot find files: inspect `CMakeLists.txt` source paths before changing Gradle.
- JNI method missing: check package, class, native method, JNI symbol, and `System.loadLibrary(...)`.
- ABI output missing: check `abiFilters`, installed NDK packages, and generated build directories.
- Version upgrade broke build: revert only the version change you made and return to pinned repo versions.
- Android CLI cannot create the desired native template: create the nearest official app shell and overlay only missing native files.

## Optional References

- Agent install paths: `references/agent-adapters.md`
- Android CLI install/details: `references/android-cli-notes.md`
- Explicit latest-version work: `references/cutting-edge-android.md`
