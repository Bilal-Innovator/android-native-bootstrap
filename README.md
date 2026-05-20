# Android Native Bootstrap Skill

A reusable AI-agent skill for bootstrapping and maintaining native Android projects that combine Kotlin/Java, JNI, CMake, NDK, ABI configuration, and an isolated native C++ core module.

The skill is designed to reduce token waste and build drift when AI coding agents create or repair Android native projects. It tells agents to use the official Android CLI workflow first, reuse existing Gradle/CMake/JNI configuration, and apply this skill only where official tooling does not cover advanced native C++ setup.

## Project Overview

Android Native Bootstrap is a portable skill package for AI coding agents. It provides one concise instruction file, optional reference notes, and reusable Gradle/CMake/JNI template assets so agents can create or repair native Android project structure without repeatedly inventing setup code for high-performance native engines, shared native runtimes, cross-platform C++ cores, or performance-critical native layers.

## Problem

AI coding tools often spend too many tokens rediscovering the same Android native setup details:

- Android NDK setup
- CMake and `native-lib.cpp`
- Gradle `externalNativeBuild`
- ABI filters and NDK version pinning
- JNI bridge naming and package drift
- Folder structure generation
- Trial-and-error build fixes

This repository turns those repeated decisions into a deterministic protocol plus reusable templates.

## Goals

- Prefer official Android CLI workflows over hand-written setup.
- Reuse existing Gradle, CMake, and JNI files when a project already exists.
- Keep native C++ core modules isolated and reusable.
- Avoid duplicate bootstrap logic across AI tools.
- Minimize token usage through templates, references, and incremental patches.
- Keep builds deterministic, Android-compliant, and easy to validate.
- Support stable production projects and explicit cutting-edge Android stacks.

## Supported AI Agents And Tools

This skill can be used with:

- Codex
- Cursor
- Claude Code
- Antigravity / Gemini workflows
- Other AI coding agents that support repo rules, custom instructions, skills, or file references

The skill is tool-agnostic, but it is structured as a Codex-style skill folder with `SKILL.md`, `references/`, `assets/`, and optional agent metadata.

## Repository Contents

```text
android-native-bootstrap/
  SKILL.md
  README.md
  agents/
    openai.yaml
  assets/
    native-android-cmake-template/
      build.gradle.kts
      settings.gradle.kts
      gradle/libs.versions.toml
      app/
        build.gradle.kts
        src/main/
          AndroidManifest.xml
          java/com/example/nativeengine/NativeEngine.kt
          cpp/
            CMakeLists.txt
            native-lib.cpp
            core/native_engine.h
            core/native_engine.cpp
  references/
    agent-adapters.md
    android-cli-notes.md
    cutting-edge-android.md
```

## Installation

### Codex

Copy the full skill folder into your Codex skills directory:

```powershell
Copy-Item `
  -Recurse `
  -Force `
  "android-native-bootstrap" `
  "$env:USERPROFILE\.codex\skills\android-native-bootstrap"
```

Then invoke it:

```text
Use $android-native-bootstrap to add JNI/CMake/NDK support to this Android project.
```

### Cursor

Keep this repository in your project or a shared tools directory, then create:

```text
.cursor/rules/android-native-bootstrap.mdc
```

The rule should reference:

```text
android-native-bootstrap/SKILL.md
android-native-bootstrap/assets/native-android-cmake-template/
```

Apply the rule when editing Android, Gradle, CMake, JNI, NDK, or native C++ engine files.

### Claude Code

Add a repository-level or user-level instruction that points Claude Code to:

```text
android-native-bootstrap/SKILL.md
```

Tell it to use the official Android CLI workflow first and this skill only as the native C++ overlay.

### Antigravity / Gemini Android CLI Workflow

Antigravity does not discover skills from a folder placed directly under `.antigravity/` or `.gemini/`.

Use one of these supported skill locations:

Workspace-specific:

```text
<workspace-root>/.agents/skills/android-native-bootstrap/
```

Global:

```text
%USERPROFILE%\.gemini\antigravity\skills\android-native-bootstrap\
```

Copy the full skill folder to one of those locations. Then enable the official Android CLI workflow:

```text
android init
android skills add android-cli
```

Then use this skill as the project-specific JNI/CMake/NDK extension.

## Suggested Installation Targets

| Tool | Suggested target |
| --- | --- |
| Codex | `%USERPROFILE%\.codex\skills\android-native-bootstrap\` |
| Cursor | `.cursor/rules/android-native-bootstrap.mdc` plus this folder in the repo |
| Claude Code | Repo or user-level instruction referencing `SKILL.md` |
| Antigravity workspace skill | `<workspace-root>/.agents/skills/android-native-bootstrap/` |
| Antigravity global skill | `%USERPROFILE%\.gemini\antigravity\skills\android-native-bootstrap\` |
| Gemini CLI context fallback | `GEMINI.md` that references `android-native-bootstrap/SKILL.md` |
| Other agents | Any skill, memory, rule, or instruction system that can reference files |

Keep the entire folder together. `SKILL.md`, `references/`, and `assets/` are one unit.

## Android CLI Integration

This skill is intentionally layered on top of the official Android CLI workflow.

Use Android CLI for:

- Project creation
- Project inspection
- SDK package management
- Android documentation lookup
- Deployment
- Official agent skill setup

Useful commands:

```bash
android init
android info
android skills list
android skills add android-cli
android create -h
android create --list
android describe --project_dir=<project-root>
android docs search "Android NDK CMake externalNativeBuild"
android sdk list "ndk|cmake|platforms|build-tools"
```

Use this custom skill only when Android CLI support is insufficient for JNI, CMake, NDK, ABI filters, shared native runtimes, or reusable native C++ core modules.

## JNI, CMake, And NDK Guidance

Recommended native layout:

```text
app/src/main/cpp/
  CMakeLists.txt
  native-lib.cpp
  core/
    native_engine.h
    native_engine.cpp
```

Rules:

- Keep JNI code in `native-lib.cpp`.
- Keep reusable C++ engine/runtime logic in `core/`.
- Do not include `jni.h` in the reusable C++ core.
- Keep CMake targets deterministic.
- Pin ABI filters in one Gradle location.
- Preserve existing Gradle, CMake, and JNI files when they are already coherent.

Default ABI set:

```kotlin
ndk {
    abiFilters += listOf("arm64-v8a", "armeabi-v7a", "x86_64")
}
```

## Recommended Project Structure

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

## Token Optimization Principles

- Use Android CLI before manual setup.
- Read existing files before editing.
- Patch incrementally instead of regenerating full projects.
- Copy native templates only when official Android CLI output lacks native support.
- Keep long details in `references/` and load them only when needed.
- Keep boilerplate in `assets/` so agents do not rewrite it from memory.
- Avoid unnecessary CLI executions.
- Avoid dependency upgrades unless requested or required.
- Use cutting-edge versions only in explicit cutting-edge mode.

## Example Workflows

### Add Native Support To An Existing Android Project

```text
Use $android-native-bootstrap to add JNI/CMake/NDK support to this existing Android project. Prefer Android CLI project inspection first, preserve existing Gradle files, and add only the missing native C++ structure.
```

Expected behavior:

1. Inspect the project with Android CLI and existing Gradle files.
2. Reuse current project structure.
3. Add `CMakeLists.txt`, `native-lib.cpp`, and `core/` only if missing.
4. Patch Gradle `externalNativeBuild` minimally.
5. Validate with the narrowest Gradle native build task.

### Bootstrap A New Native Engine App

```text
Use $android-native-bootstrap to create a native Android project with a reusable high-performance C++ core module.
```

Expected behavior:

1. Use Android CLI to create the Android app shell.
2. Overlay the native template from `assets/native-android-cmake-template/`.
3. Patch package names and app identifiers.
4. Validate incrementally.

### Use Latest Android Stack

```text
Use $android-native-bootstrap in cutting-edge mode for a new native Android app with a performance-critical C++ layer.
```

Expected behavior:

1. Verify current official versions.
2. Upgrade AGP, Gradle, Kotlin, Compose BOM, SDK, NDK, and CMake coherently.
3. Keep versions in `gradle/libs.versions.toml`.
4. Avoid preview/canary versions unless explicitly requested.

## Troubleshooting

### Antigravity Does Not Detect The Skill

Make sure the folder is not installed as:

```text
<workspace-root>/.antigravity/android-native-bootstrap/
<workspace-root>/.gemini/android-native-bootstrap/
```

Those are not Antigravity skill discovery paths.

Use one of these instead:

```text
<workspace-root>/.agents/skills/android-native-bootstrap/
%USERPROFILE%\.gemini\antigravity\skills\android-native-bootstrap\
```

The final path must contain `SKILL.md` directly:

```text
.../skills/android-native-bootstrap/SKILL.md
```

Restart Antigravity or start a new agent session after copying the folder. In a prompt, invoke it explicitly:

```text
Use the android-native-bootstrap skill to add JNI/CMake/NDK support to this project.
```

For Gemini CLI, create or update a project `GEMINI.md` file and point it at:

```text
android-native-bootstrap/SKILL.md
```

You can also copy the ready-made adapter from:

```text
android-native-bootstrap/adapters/GEMINI.md
```

### Android CLI Is Not Installed

Install Android CLI from the official Android documentation. On Windows:

```powershell
winget install --id Google.AndroidCLI
```

Verify:

```bash
android info
```

Without Android CLI, agents may use the bundled templates as an offline fallback, but project creation and SDK inspection will be less deterministic.

### Android CLI Syntax Differs From The Docs

Run:

```bash
android create -h
```

Follow the installed CLI help output. Some versions use `android create --list`; others may document `android create list`.

### CMake Cannot Find Source Files

Check paths in:

```text
app/src/main/cpp/CMakeLists.txt
```

Do not rewrite Gradle until CMake source paths are verified.

### JNI Method Not Found At Runtime

Check:

- Package name
- Kotlin/Java class name
- Native method name
- JNI symbol in `native-lib.cpp`
- Loaded library name in `System.loadLibrary(...)`

### ABI Output Is Missing

Check:

- `abiFilters`
- Installed NDK packages
- `externalNativeBuild`
- Generated build output directories

### Build Breaks After Version Upgrade

Use stable deterministic mode unless cutting-edge mode was explicitly requested. Revert only the version changes made by the agent, then restore the repo's pinned versions.

## Contributing

Contributions are welcome.

Good contributions include:

- Better Android CLI compatibility notes
- More robust JNI/CMake templates
- Additional native engine examples
- Agent adapter improvements
- Build validation scripts
- Documentation that reduces repeated AI-agent token usage

Contribution guidelines:

1. Keep `SKILL.md` concise.
2. Put detailed material in `references/`.
3. Put reusable boilerplate in `assets/`.
4. Do not add large dependencies without a clear native Android use case.
5. Preserve deterministic defaults.
6. Prefer official Android CLI workflows over custom bootstrap logic.
7. Test template changes in a real Android project when possible.

## License

MIT License. See `LICENSE`.
