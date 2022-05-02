#Requires -RunAsAdministrator
param($uninstallFlag)

$installLocation = "C:\GIFCopier\"
$FFkey = "HKCU:\SOFTWARE\Mozilla\NativeMessagingHosts\com.syanth.gifcopier"
$ChromeKey = "HKCU:\SOFTWARE\Google\Chrome\NativeMessagingHosts\com.syanth.gifcopier"
$EdgeKey = "HKCU:\SOFTWARE\Microsoft\Edge\NativeMessagingHosts\com.syanth.gifcopier"

if ($uninstallFlag) {
    $confirmation = Read-Host "Are you sure you want to uninstall GIFCopier? (y/n)"
    if ($confirmation -eq 'y') {
        Remove-Item $installLocation -Force -Recurse
        # Remove Registries
        Remove-Item -Path $FFkey -Force
        Remove-Item -Path $ChromeKey -Force
        Remove-Item -Path $EdgeKey -Force
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

Expand-Archive -Path "clipapp.zip" -DestinationPath $installLocation
if (-not $?) {
    Exit -1
}

function CheckAndCreateKey {
    param (
        $regPath
    )

    $key = try {
        Get-Item -Path $regPath -ErrorAction Stop
    }
    catch {
        New-Item -Path $regPath -Force
    }
    return $key
}

function Add-ManifestKey {
    param (
        $regPath,
        $manifestPath
    )

    $key = CheckAndCreateKey $regPath
    New-ItemProperty -Path $key.PSPath -Name "(Default)" -Value $manifestPath
}

Add-ManifestKey $FFkey ($installLocation + "\com.syanth.gifcopier.firefox.json")
Add-ManifestKey $ChromeKey ($installLocation + "\com.syanth.gifcopier.chrome.json")
Add-ManifestKey $EdgeKey ($installLocation + "\com.syanth.gifcopier.edge.json")

CheckAndCreateKey "HKLM:\SOFTWARE\Policies\Google"
CheckAndCreateKey "HKLM:\SOFTWARE\Policies\Google\Chrome"
CheckAndCreateKey "HKLM:\SOFTWARE\Policies\Google\Chrome\ExtensionInstallWhitelist"
New-ItemProperty -Path "HKLM:\SOFTWARE\Policies\Google\Chrome\ExtensionInstallWhitelist" -Name "1" -Value "ncddcifdiglpdkflenjfceajajjmglji"

# Open Browsers at App store pages

Start-Process "C:\Program Files\Mozilla Firefox\firefox.exe" "google.com"
Start-Process "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" "google.com"
Start-Process "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" "google.com"