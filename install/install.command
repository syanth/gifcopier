installLocation="/Applications/"

cd "$(dirname "$0")"

if [ -d "${installLocation}GIFCopier" ];
then
    echo "GIFCopier is already installed. Do you want to uninstall GIFCopier? (y/n)"
    read confirmation
    if [ $confirmation == 'y' ];
    then
        echo "Uninstalling..."
        rm -rf "${installLocation}GIFCopier"
    else
        echo "Exiting."
        exit 0
    fi
fi

echo "Do you want to install GIFCopier? (y/n)"
read confirmation
if [ $confirmation == 'y' ];
then
    echo "Installing"
else
    echo "Exiting."
    exit 0
fi

# Copy over files
unzip clipapp.zip -d $installLocation -x '__MACOSX/*'

# Copy over Native Manifests

cp /usr/local/GIFCopier/com.syanth.gifcopier.firefox.mac.json ~/"Library/Application Support/Mozilla/NativeMessagingHosts/com.syanth.gifcopier.json"
cp /usr/local/GIFCopier/com.syanth.gifcopier.chrome.mac.json ~/"Library/Application Support/Google/Chrome/NativeMessagingHosts/com.syanth.gifcopier.json"
cp /usr/local/GIFCopier/com.syanth.gifcopier.chrome.mac.json ~/"Library/Application Support/Microsoft Edge/NativeMessagingHosts/com.syanth.gifcopier.json"

# Open Browsers at App Store Pages

open -n -a "Firefox" --args "--new-window" "google.com"
open -n -a "Google Chrome" --args "--new-window" "google.com"
open -n -a "Microsoft Edge" --args "--new-window" "google.com"