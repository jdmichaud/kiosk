import QtQuick 2.2
import QtQuick.Window 2.2
import QtWebView 1.1

WebView {
  id: webview
  visible: true
  url: "https://www.google.com"
  width: Window.width
  height: Window.height
  onLoadingChanged: {
    if (loadRequest.errorString)
      console.error(loadRequest.errorString);
  }
}
