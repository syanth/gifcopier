rm -r dist_chrome
cp -R src dist_chrome
rm dist_chrome/manifest.json
mv dist_chrome/manifest.chrome.json dist_chrome/manifest.json

rm -r dist_firefox
cp -R src dist_firefox
rm dist_firefox/manifest.chrome.json