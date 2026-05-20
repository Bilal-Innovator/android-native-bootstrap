# Cutting-Edge Android Version Policy

Use this only when the user explicitly asks for latest/cutting-edge/preview/current Android frameworks, plugins, libraries, Gradle, or AGP.

## Current Baseline

Checked on 2026-05-20 from official Android and Kotlin sources:

- AGP `9.2.0`
- Gradle `9.4.1`
- SDK Build Tools `36.0.0`
- AGP 9.2 default NDK `28.2.13676358`
- JDK `17`
- Compose BOM `2026.05.00`
- Kotlin `2.3.20`

Official source URLs:

- https://developer.android.com/build/releases/agp-9-2-0-release-notes
- https://developer.android.com/develop/ui/compose/bom
- https://kotlinlang.org/docs/whatsnew2320.html

## Rules

1. Re-check official sources before using these versions after 2026-05-20.
2. Prefer stable latest over alpha/beta/canary.
3. Use preview/canary only when the user explicitly asks or a required API exists only there.
4. Upgrade version sets coherently:
   - AGP with the required Gradle wrapper.
   - Kotlin with the Kotlin Compose plugin.
   - Compose libraries through the Compose BOM.
   - NDK/CMake through Android SDK-managed packages.
5. Keep dependency versions in `gradle/libs.versions.toml` when creating a new project.
6. Do not add large framework stacks speculatively. Add only libraries required by the app architecture.

## Recommended Modern Android Stack

For native Android apps with a Kotlin UI and a performance-critical native layer:

- Kotlin
- AndroidX Core
- Jetpack Compose with Compose BOM
- Material 3 when UI is required
- Lifecycle Runtime Compose for screen lifecycle
- Android Gradle Plugin latest stable
- CMake through `externalNativeBuild`
- NDK pinned to the AGP default unless the project needs a specific NDK

Avoid introducing Hilt, Room, CameraX, Media3, OpenCV, Vulkan, RenderScript alternatives, ML libraries, or domain-specific frameworks unless the user asks or the native feature requires them.
