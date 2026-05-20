$ErrorActionPreference = "Stop"

$android = Get-Command android -ErrorAction SilentlyContinue

if (-not $android) {
    $wingetAndroid = Get-ChildItem `
        -Path (Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages") `
        -Recurse `
        -Filter android.exe `
        -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -like "*Google.AndroidCLI*" } |
        Select-Object -First 1

    if ($wingetAndroid) {
        Write-Host "[WARN] Android CLI is installed but not on PATH:"
        Write-Host $wingetAndroid.FullName
        Write-Host ""
        Write-Host "Add its folder to PATH or restart your terminal/agent environment."
        Write-Host ""
        & $wingetAndroid.FullName info
        exit 0
    }
}

if (-not $android) {
    Write-Host "[MISS] Android CLI was not found on PATH."
    Write-Host ""
    Write-Host "Install from:"
    Write-Host "https://developer.android.com/tools/agents/android-cli/download"
    Write-Host ""
    Write-Host "Windows:"
    Write-Host "winget install --id Google.AndroidCLI"
    exit 1
}

Write-Host "[OK] Android CLI found:"
Write-Host $android.Source
Write-Host ""
android info
