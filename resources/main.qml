import QtQuick 2.2
import QtQuick.Window 2.2
import QtWebView 1.1

WebView {
  id: webview
  visible: true
  url: context.getUrl()
  width: Window.width
  height: Window.height
  onLoadingChanged: {
    if (loadRequest.errorString)
      console.error(loadRequest.errorString);
  }

  Connections {
    target: context
    onUrlChanged: console.log('url changed to', context)
  }
}
