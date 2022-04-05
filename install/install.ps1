#Requires -RunAsAdministrator
param($uninstallFlag)

$installLocation = "C:\Program Files\GIFCopier"

if ($uninstallFlag) {
    $confirmation = Read-Host "Are you sure you want to uninstall GIFCopier? (y/n)"
    if ($confirmation -eq 'y') {
        Remove-Item $installLocation -Force -Recurse
        # Remove Registries
        Remove-Item -Path "HKCU:\SOFTWARE\Mozilla\NativeMessagingHosts\com.syanth.gifcopier" -Force
        Remove-Item -Path "HKCU:\SOFTWARE\Google\Chrome\NativeMessagingHosts\com.syanth.gifcopier" -Force
        Remove-Item -Path "HKCU:\SOFTWARE\Microsoft\Edge\NativeMessagingHosts\com.syanth.gifcopier" -Force
    }
    else {
        Write-Host "Exiting."
        Exit 1
    }
    Exit
}

$confirmationText = "Do you want to install GIFCopier? (y/n)"
# Copy over executables
if (Test-Path -Path $installLocation) {
    $confirmationText = "GIFCopier directory already exists. Re-install? (y/n)"
}
$confirmation = Read-Host $confirmationText
if ($confirmation -eq 'y') {
    Remove-Item $installLocation -Force -Recurse
}
else {
    Write-Host "Exiting."
    Exit 1
}

mkdir $installLocation

Expand-Archive -Path "clipapp.zip" -DestinationPath "C:\Program Files\GIFCopier\"
if (-not $?) {
    Exit -1
}
Copy-Item -Path "install.ps1" -Destination "C:\Program Files\GIFCopier\"
Copy-Item -Path "uninstall.cmd" -Destination "C:\Program Files\GIFCopier\"

function Add-ManifestKey {
    param (
        $regPath,
        $manifestPath
    )

    $key = try {
        Get-Item -Path $regPath -ErrorAction Stop
    }
    catch {
        New-Item -Path $regPath -Force
    }
    New-ItemProperty -Path $key.PSPath -Name "(Default)" -Value $manifestPath
}

Add-ManifestKey "HKCU:\SOFTWARE\Mozilla\NativeMessagingHosts\com.syanth.gifcopier" "C:\Program Files\GIFCopier\com.syanth.gifcopier.firefox.json"
Add-ManifestKey "HKCU:\SOFTWARE\Google\Chrome\NativeMessagingHosts\com.syanth.gifcopier" "C:\Program Files\GIFCopier\com.syanth.gifcopier.chrome.json"
Add-ManifestKey "HKCU:\SOFTWARE\Microsoft\Edge\NativeMessagingHosts\com.syanth.gifcopier" "C:\Program Files\GIFCopier\com.syanth.gifcopier.chrome.json"

# Open Browsers at App store pages
Start-Process "C:\Program Files\Mozilla Firefox\firefox.exe" "google.com"
Start-Process "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" "google.com"
Start-Process "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" "google.com"