#include "main.h"
#include "web_browser.h"


IMPLEMENT_APP(WBrowserInit)


bool WBrowserInit::OnInit()
{
    WebBrowser *browser = new WebBrowser(wxT("Browser"));
    browser->noAddrCompletion = false;
    // browser->SetTabWidgets();

    // wxInitAllImageHandlers();
    return browser->Show(true);
}

