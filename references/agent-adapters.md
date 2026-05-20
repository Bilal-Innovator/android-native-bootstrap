# Agent Adapters

Keep one source of truth: this skill folder. For each agent, point its native instruction mechanism at `SKILL.md` and keep the template assets in place.

## Suggested Installation Targets

Keep the whole `android-native-bootstrap/` folder together. `SKILL.md`, `references/`, and `assets/` are a single unit.

### Codex

Install target:

```text
%USERPROFILE%\.codex\skills\android-native-bootstrap\
```

Copy the full folder there. Invoke it with:

```text
Use $android-native-bootstrap to add JNI/CMake/NDK support to this Android project.
```

### Claude Code

Use either a repository-level instruction file or a user-level custom instruction that points to:

```text
android-native-bootstrap/SKILL.md
```

Keep this folder inside the repository or in a shared local skills directory. Tell Claude Code to read `SKILL.md` first and to use `assets/native-android-cmake-template/` only as a native overlay.

### Cursor

Create a repo rule:

```text
.cursor/rules/android-native-bootstrap.mdc
```

In that rule, reference:

```text
android-native-bootstrap/SKILL.md
android-native-bootstrap/assets/native-android-cmake-template/
```

Set the rule to apply when editing Android, Gradle, CMake, JNI, NDK, or C++ native engine files.

### Antigravity / Gemini Android CLI Workflow

First enable the official Android CLI workflow:

```text
android init
android skills add android-cli
```

Then add this skill as the project-specific native CMake/JNI extension. Use it only after Android CLI has created, inspected, or described the Android project.

### Other AI Coding Agents

Use the agent's repo rules, memory, skill, or custom instruction feature to point at:

```text
android-native-bootstrap/SKILL.md
```

Do not paste the whole skill into the agent prompt if the agent can read files. Give the agent the folder path and the minimal adapter text below.

Minimal adapter text:

```text
Use the Android Native Bootstrap protocol from android-native-bootstrap/SKILL.md.
Prefer the official Android CLI skill/workflows for Android project creation, project description, SDK management, docs lookup, and deployment. Use this custom protocol only when official Android CLI support is insufficient for JNI, CMake, NDK, ABI filters, shared native runtimes, or reusable native C++ core modules. Reuse existing Gradle/CMake/JNI configs, avoid duplicate bootstrap logic, patch incrementally, avoid unnecessary CLI executions, preserve deterministic Android-compliant builds, and copy JNI/CMake assets from assets/native-android-cmake-template only as a native overlay.
```

Do not paste the entire skill into every agent rule if the agent can reference files. File references keep token use low and avoid drift.
