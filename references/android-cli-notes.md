# Android CLI Notes

Official page checked: https://developer.android.com/tools/agents/android-cli

Last documented update observed: 2026-05-07 UTC for the overview page; download page observed updated 2026-05-19 UTC.

Use Android CLI as the first source of Android agent automation:

- `android init` installs the `android-cli` skill for agents.
- `android info` reports the SDK path and Android CLI version.
- `android create` initializes projects from official templates.
- `android create --dry-run --verbose` previews project creation.
- `android create list` lists templates.
- `android describe --project_dir=<project>` emits project metadata and artifact paths.
- `android docs search` and `android docs fetch` query Android Knowledge Base material.
- `android sdk list`, `android sdk update`, and `android sdk remove` manage SDK packages.
- `android run --apks=<apk-paths>` deploys already-built APKs; it does not build.
- `android skills list/find/add/remove` manages Android skills for detected agents.

Precedence rule:

- Prefer the official `android-cli` skill/workflow for normal Android project bootstrap, SDK management, docs lookup, template generation, describing projects, and deployment.
- Use `android-native-bootstrap` only as an extension for JNI, CMake, NDK, ABI, and native C++ engine concerns that Android CLI does not fully cover.
- Reuse Android CLI output and existing Gradle/CMake/JNI files. Avoid duplicate bootstrap logic.
- Run CLI commands intentionally. Do not repeat discovery commands unless project files or installed tools changed.

Known Windows notes from the official docs:

- `android emulator` is currently disabled on Windows.
- Downloading Android CLI from Windows PowerShell is currently unsupported.
- Windows install options include `winget install --id Google.AndroidCLI`, `curl.exe ... install.cmd`, or direct download.

Observed local compatibility note on Windows, 2026-05-20:

- Installed Android CLI reported version `0.7.15378687`.
- Local help used `android create --list` rather than `android create list`.
- Local help required `--name=<applicationName>` for `android create`.
- Local template list returned `empty-activity (default)` with tags `compose, activity, agp-9`.
- Local help did not show `--dry-run`; treat dry-run as version-dependent.
- Running Android CLI inside a filesystem sandbox can fail while writing analytics files under `%USERPROFILE%\.android\cli\analytics`; rerun with normal user filesystem access or fix permissions.
