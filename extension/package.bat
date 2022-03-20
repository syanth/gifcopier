rmdir dist_chrome /s /q
Xcopy /q /s /e src dist_chrome\
del dist_chrome\manifest.firefox.json
ren dist_chrome\manifest.chrome.json manifest.json

rmdir dist_firefox /s /q
Xcopy /q /s /e src dist_firefox\
del dist_firefox\manifest.chrome.json
ren dist_firefox\manifest.firefox.json manifest.json