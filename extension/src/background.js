import browser from "webextension-polyfill"

var port = browser.runtime.connectNative("com.syanth.clipcopier")

function onResponse(response) {
    console.log("Received " + JSON.stringify(response));
}
  
function onError(error) {
    console.log(`Error: ${error}`);
}

browser.contextMenus.create({
    id: "copy-gifv",
    title: "Copy GIFV",
    contexts: ["video"]
});

browser.contextMenus.create({
    id: "copy-gif",
    title: "Copy GIF",
    contexts: ["image"],
    "targetUrlPatterns":["*://*/*.gif"]
});

browser.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === "copy-gifv") {
        var sending = browser.runtime.sendNativeMessage(
            "com.syanth.clipcopier",
            info.srcUrl);
          sending.then(onResponse, onError);
    }
    else if (info.menuItemId === "copy-gif") {
        var sending = browser.runtime.sendNativeMessage(
            "com.syanth.clipcopier",
            info.srcUrl);
        sending.then(onResponse, onError);
    }
}
);