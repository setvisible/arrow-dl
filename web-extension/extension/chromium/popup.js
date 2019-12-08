"use strict";

const application = 'com.setvisible.downrightnow';

/* ***************************** */
/* Native Message                */
/* ***************************** */
function checkConnection() {
  var data = "areyouthere";
  chrome.runtime.sendNativeMessage(application,
    { text: "areyouthere" },
    onHelloResponse);
};

function onHelloResponse(response) {
  if (chrome.runtime.lastError) {
    console.log(chrome.runtime.lastError.message);
    onHelloError(response);
  }
  if (response === undefined) {
    onHelloError(response);
  } else {
    showWarningMessage(false);
  }
};

function onHelloError(error) {
  console.log(`Error: ${error}`);
  showWarningMessage(true);
};


/* ***************************** */
/* Core                          */
/* ***************************** */
function showWarningMessage(hasError) {
  var x = document.getElementById("warning-area");
  if (hasError) {
    x.style.display = "block";
  } else {
    x.style.display = "none";
  }
  setDisabled("button-start", hasError);
  setDisabled("button-manager", hasError);
  setDisabled("button-preference", hasError);
};

function setDisabled(name, hasError) {
  if (hasError) {
    document.getElementById(name).classList.add('disabled');
  } else {
    document.getElementById(name).classList.remove('disabled');
  }
};

/* ***************************** */
/* Events                        */
/* ***************************** */
function checkInstallation() {
  checkConnection();
};

document.addEventListener('DOMContentLoaded', checkInstallation); 

document.getElementById("button-start").addEventListener('click', () => {
    // Call collectDOMandSendData() from 'background.js'
    chrome.extension.getBackgroundPage().collectDOMandSendData();
    window.close();
});

document.getElementById("button-manager").addEventListener('click', () => { 
    var command = "[MANAGER]";
    chrome.extension.getBackgroundPage().sendData(command);
    window.close();
});

document.getElementById("button-preference").addEventListener('click', () => { 
    var command = "[PREFS]";
    chrome.extension.getBackgroundPage().sendData(command);
    window.close();
});

document.getElementById("button-options-page").addEventListener('click', () => {
    var openingPage = chrome.runtime.openOptionsPage();
    window.close();
});
