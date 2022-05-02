if (typeof browser === "undefined") {
    var browser = chrome;
}

function onResponse(response) {
    console.log("Received " + JSON.stringify(response));
}
  
function onError(error) {
    console.log(`Error: ${error}`);
}

chrome.runtime.onInstalled.addListener(() => {
    browser.contextMenus.create({
        id: "copy-gifv",
        title: "Copy GIFV",
        contexts: ["video"]
    });
    browser.contextMenus.create({
        id: "copy-gif",
        title: "Copy GIF as MP4",
        contexts: ["image"],
        "targetUrlPatterns":["*://*/*.gif*"]
    });
});

browser.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === "copy-gifv") {
        var sending = browser.runtime.sendNativeMessage(
            "com.syanth.gifcopier",
            {"text": info.srcUrl});
          sending.then(onResponse, onError);
    }
    else if (info.menuItemId === "copy-gif") {
        var sending = browser.runtime.sendNativeMessage(
            "com.syanth.gifcopier",
            {"text": info.srcUrl});
        sending.then(onResponse, onError);
    }
});