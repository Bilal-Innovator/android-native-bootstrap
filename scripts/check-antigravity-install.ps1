param(
    [string] $WorkspaceRoot = (Get-Location).Path
)

$locations = @(
    (Join-Path $HOME ".gemini\config\skills\android-native-bootstrap"),
    (Join-Path $WorkspaceRoot ".agents\skills\android-native-bootstrap"),
    (Join-Path $WorkspaceRoot ".agent\skills\android-native-bootstrap"),
    (Join-Path $HOME ".gemini\antigravity\skills\android-native-bootstrap")
)

foreach ($location in $locations) {
    $skillFile = Join-Path $location "SKILL.md"
    if (Test-Path $skillFile) {
        Write-Host "[OK] $skillFile"
    } else {
        Write-Host "[MISS] $skillFile"
    }
}

Write-Host ""
Write-Host "Antigravity does not detect skills from:"
Write-Host "  <workspace-root>\.antigravity\android-native-bootstrap"
Write-Host "  <workspace-root>\.gemini\android-native-bootstrap"
