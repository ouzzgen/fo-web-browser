#include "main.h"
#include "web_browser.h"


IMPLEMENT_APP(WBrowserInit)


bool WBrowserInit::OnInit()
{
    WebBrowser *browser = new WebBrowser(wxT("Browser"));
    // wxInitAllImageHandlers();
    return browser->Show(true);
}

