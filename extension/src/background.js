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

browser.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === "copy-gifv") {
        console.log(info);
        console.log("Original URL: ", info.srcUrl);
        let fixedURL = getURL(info.srcUrl);
        console.log("Fixed URL: ", fixedURL)
        console.log("Sending URL");
        var sending = browser.runtime.sendNativeMessage(
          "com.syanth.clipcopier",
          fixedURL);
        sending.then(onResponse, onError);
    }
}
);

function getURL(URL) {
    if (URL.includes("preview.redd.it") && !URL.includes("external")) {
        URL = URL.replace("preview", "i");
        return URL;
    }
    return URL
}