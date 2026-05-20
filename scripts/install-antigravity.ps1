param(
    [ValidateSet("config", "workspace", "global", "legacy-workspace")]
    [string] $Target = "config",

    [string] $WorkspaceRoot = (Get-Location).Path
)

$ErrorActionPreference = "Stop"

$skillRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$skillName = Split-Path $skillRoot -Leaf

if (-not (Test-Path (Join-Path $skillRoot "SKILL.md"))) {
    throw "Expected SKILL.md at $skillRoot"
}

switch ($Target) {
    "config" {
        $destination = Join-Path $HOME ".gemini\config\skills\$skillName"
    }
    "workspace" {
        $destination = Join-Path $WorkspaceRoot ".agents\skills\$skillName"
    }
    "legacy-workspace" {
        $destination = Join-Path $WorkspaceRoot ".agent\skills\$skillName"
    }
    "global" {
        $destination = Join-Path $HOME ".gemini\antigravity\skills\$skillName"
    }
}

New-Item -ItemType Directory -Force -Path (Split-Path $destination -Parent) | Out-Null

if (Test-Path $destination) {
    Remove-Item -Recurse -Force $destination
}

Copy-Item -Recurse -Force $skillRoot $destination

$requiredSkillFile = Join-Path $destination "SKILL.md"
if (-not (Test-Path $requiredSkillFile)) {
    throw "Install failed: $requiredSkillFile was not created"
}

Write-Host "Installed $skillName skill to:"
Write-Host $destination
Write-Host ""
Write-Host "Expected SKILL.md:"
Write-Host $requiredSkillFile
Write-Host ""
Write-Host "Restart Antigravity or start a new agent session, then prompt:"
Write-Host "Use the android-native-bootstrap skill to add JNI/CMake/NDK support to this project."
