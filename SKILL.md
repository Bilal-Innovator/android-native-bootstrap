---
name: android-native-bootstrap
description: Deterministic bootstrap and repair protocol for native Android projects that use Kotlin/Java plus a native C++ core module through JNI, CMake, NDK, Gradle, and ABI configuration. Use when creating, recreating, repairing, or extending Android projects with native-lib.cpp, CMakeLists.txt, externalNativeBuild, abiFilters, Android CLI for agents, Android NDK, JNI bridges, high-performance native engines, shared native runtimes, reusable C++ modules, or token-efficient Android native scaffolding.
---

# Android Native Bootstrap

## Operating Rule

Use the official Android CLI skill/workflows first, copy bundled templates only for native C++ gaps, and patch existing files third. Do not hand-generate Android, Gradle, NDK, CMake, or JNI boilerplate from memory unless Android CLI support and the existing project structure are insufficient.

This skill is an extension layer, not a replacement for the official Android CLI skill. Let Android CLI handle project discovery, official template creation, SDK package management, documentation lookup, deployment, and ordinary Android-compliant build setup. Use this custom skill only for advanced native C++ requirements such as JNI boundaries, reusable C++ core isolation, CMake target layout, ABI filters, NDK pinning, and high-performance native engine templates.

Avoid duplicate bootstrap logic. If Android CLI creates or describes a valid Gradle project, reuse that structure and overlay only the missing native pieces.

Default to build-stable pinned versions. Use cutting-edge Android frameworks, plugins, libraries, Gradle, AGP, SDK, NDK, Compose, and Jetpack libraries only when the user explicitly asks for latest/cutting-edge/preview/current versions, or when bootstrapping a brand-new experimental project.

## Fast Path

1. Inspect before editing:
   - `android info`
   - `android skills list` when deciding whether the official Android CLI skill is already available to the active agent
   - `android describe --project_dir=<project-root>` when a project exists
   - `android create -h` before creating a new app
   - `android docs search "<specific Android topic>"` before guessing
2. Avoid unnecessary CLI executions. Run each Android CLI discovery command once, reuse its output, and do not repeat commands just to reconfirm stable facts in the same task.
3. If Android CLI is missing, tell the user the exact missing command and continue with the bundled template only if they want an offline scaffold.
4. Prefer `android create --dry-run --verbose <template> --output=<dir>` before creating files when the installed CLI supports `--dry-run`; otherwise use `android create -h` and `android create --list`/`android create list` before writing.
5. Create or repair the Android shell with official Android CLI workflows. Add native/CMake files from `assets/native-android-cmake-template` only when the official template does not provide the required JNI/CMake/NDK structure.
6. Keep the performance-critical native layer in `app/src/main/cpp/core/` and the JNI bridge in `app/src/main/cpp/native-lib.cpp`.
7. Validate in small steps: sync/configure, compile native, assemble debug, then run/deploy only if requested.

## Version Mode

Choose one mode before editing versions:

- **Stable deterministic mode**: preserve existing versions and avoid upgrades. Use this for existing apps, production branches, bug fixes, and build repairs.
- **Cutting-edge mode**: verify current versions from official sources, then update the project coherently. Use this only for new projects, experiments, or explicit user requests.

In cutting-edge mode:

1. Query official sources before pinning versions:
   - `android docs search "Android Gradle plugin release notes"`
   - `android docs search "Compose BOM"`
   - `android sdk list "platforms|build-tools|ndk|cmake"`
   - Official Android Developers AGP release notes, Compose BOM docs, and Kotlin release notes when Android CLI docs are insufficient.
2. Upgrade as a compatible set, not one artifact at a time: AGP, Gradle wrapper, Kotlin plugin, Compose compiler/plugin, compileSdk, buildTools, NDK, CMake, and Jetpack BOMs must agree.
3. Prefer stable latest first. Use alpha/beta/canary only when the user explicitly asks for preview/canary or a required API is unavailable in stable.
4. Record the source and date used for the version decision in a short comment, issue note, or changelog entry if the repo has one.
5. Keep rollback easy: make version changes separately from JNI/C++ algorithm changes.

Current cutting-edge baseline checked 2026-05-20:

- Android Gradle Plugin: `9.2.0`
- Gradle: `9.4.1`
- SDK Build Tools: `36.0.0`
- Default NDK for AGP 9.2: `28.2.13676358`
- JDK: `17`
- Compose BOM: `2026.05.00`
- Kotlin Android plugin: `2.3.20` stable release observed from Kotlin official release notes

Treat these as examples, not eternal constants. Re-check before using them in future work.

## Android CLI Commands

Use these commands instead of exploring manually:

```bash
android init
android update
android info
android skills list
android skills find android-cli
android skills add android-cli
android create -h
android create list
android create --list
android create --dry-run --verbose --output=<dest> <template-name>
android create --verbose --name=<application-name> --output=<dest> <template-name>
android create --output=<dest> <template-name>
android describe --project_dir=<project-root>
android docs search "Android NDK CMake externalNativeBuild"
android docs fetch <kb-url>
android sdk list "ndk|cmake|platforms|build-tools"
android sdk update <package-name>
```

On Windows, prefer `winget install --id Google.AndroidCLI` or the official Windows installer path from Android docs. Do not suggest PowerShell download snippets for Android CLI because the official docs currently list PowerShell download as unsupported.

Android CLI syntax can differ by installed version. Always run `android info` and `android create -h`; if the installed CLI lacks `--dry-run`, uses `android create --list`, or requires `--name`, follow that local help output over stale assumptions.

Use `android skills add android-cli` only when the official Android CLI skill is missing and the active agent supports Android CLI skills. Do not install or re-add skills repeatedly if they are already available.

## Project Shape

Use this stable structure unless the existing repository already has a different documented architecture:

```text
<root>/
  settings.gradle.kts
  build.gradle.kts
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

The `app/src/main/cpp/core/` module must be plain C++ with no JNI includes. Only `native-lib.cpp` may include `jni.h`.

## Template Assets

Copy from `assets/native-android-cmake-template/` only when official Android CLI output or the existing project lacks native C++ support:

- `settings.gradle.kts`
- root `build.gradle.kts`
- `gradle/libs.versions.toml`
- `app/build.gradle.kts`
- `app/src/main/AndroidManifest.xml`
- `app/src/main/cpp/CMakeLists.txt`
- `app/src/main/cpp/native-lib.cpp`
- `app/src/main/cpp/core/native_engine.h`
- `app/src/main/cpp/core/native_engine.cpp`
- `app/src/main/java/com/example/nativeengine/NativeEngine.kt`
- `app/src/main/res/values/strings.xml`

After copying, patch only package names, namespace, app id, SDK versions, ABI list, and function names that are actually required by the user. Prefer reusing existing Gradle, CMake, and JNI configs over replacing them with these templates.

For non-Codex agents or repo-local rule files, load `references/agent-adapters.md` only when the user asks to install or adapt this protocol for Cursor, Claude Code, Antigravity, Gemini, or another agent.

For latest-version bootstraps, load `references/cutting-edge-android.md` before editing Gradle, SDK, NDK, Compose, or Jetpack dependencies.

## Gradle And NDK Guardrails

- Prefer Kotlin DSL if the project already uses it; otherwise preserve the existing Gradle DSL.
- Do not upgrade Android Gradle Plugin, Gradle wrapper, Kotlin, CMake, or NDK versions unless the build requires it, the user asks, or cutting-edge mode is active.
- Pin ABI configuration in one place:

```kotlin
ndk {
    abiFilters += listOf("arm64-v8a", "armeabi-v7a", "x86_64")
}
```

- Keep `externalNativeBuild.cmake.path` pointed at `src/main/cpp/CMakeLists.txt`.
- Set `cppFlags` narrowly, usually `-std=c++17 -fexceptions -frtti`.
- Add dependencies only after proving the platform/template cannot provide the needed behavior.

When adding libraries in cutting-edge mode, prefer platform-managed and BOM-managed dependency sets:

- Use Compose BOM for Compose artifacts.
- Use Firebase BOM if Firebase is introduced.
- Use version catalogs for explicit versions.
- Avoid hardcoding versions inline in multiple Gradle files.

## JNI Rules

- Keep JNI methods small: validate inputs, translate arrays/bitmaps/buffers, call the C++ core, translate results.
- Put real algorithms in `core/` files so they can be unit-tested or reused outside Android.
- Use deterministic names:
  - Kotlin/Java facade: `NativeEngine`
  - JNI file: `native-lib.cpp`
  - CMake library target: `native_engine`
- When renaming packages, update JNI symbol names or use explicit registration. For simple bootstrap projects, generated JNI symbol names are acceptable.

## Editing Protocol

1. Read the existing project files before modifying: `settings.gradle*`, root `build.gradle*`, module `build.gradle*`, `CMakeLists.txt`, and JNI files.
2. Reuse existing Gradle/CMake/JNI configs whenever they are coherent. Patch existing files with minimal diffs. Do not rewrite whole Gradle files to match the template if the existing file is buildable.
3. Preserve the user's architecture and naming unless it conflicts with JNI/CMake correctness.
4. Generate only incremental native APIs requested by the task.
5. Keep comments sparse and useful.
6. Avoid full regeneration when an incremental change can make the build Android-compliant and deterministic.
7. Stop and report the exact blocker if SDK, NDK, CMake, or Android CLI tools are missing and installation requires user approval.

## Validation Ladder

Run the narrowest useful check first:

```bash
android describe --project_dir=<project-root>
./gradlew :app:tasks
./gradlew :app:externalNativeBuildDebug
./gradlew :app:assembleDebug
android run --apks=<apk-path>
```

On Windows, use `.\gradlew.bat` when present. If `externalNativeBuildDebug` is unavailable, inspect `./gradlew :app:tasks --all` and use the closest generated native build task.

## Failure Handling

- If CMake cannot find source files, inspect paths before changing Gradle.
- If JNI symbols fail at runtime, check package/class/function names before touching CMake.
- If ABI output is missing, check `abiFilters`, installed NDK ABIs, and generated build directories.
- If Gradle sync fails after a version change, revert only the version change you made and return to the repo's pinned versions.
- If Android CLI cannot create the exact native template, create the nearest official app template and overlay only the native template assets.
