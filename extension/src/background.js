import browser from "webextension-polyfill"

browser.contextMenus.create({
    id: "copy-gifv",
    title: "Copy GIFV",
    contexts: ["video"]
});

browser.contextMenus.create({
    id: "paste-clip",
    title: "Paste Clip",
    contexts: ["editable"]
});

browser.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === "copy-gifv") {
        console.log(info.srcUrl);
        display(info.srcUrl);
    }
}
);