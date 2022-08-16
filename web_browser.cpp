#include "web_browser.h"
using namespace std;


BEGIN_EVENT_TABLE(WebBrowser, wxFrame)
    EVT_LEFT_DCLICK(WebBrowser::MFileDownload)
    EVT_RIGHT_DCLICK(WebBrowser::MFileDownload)
    EVT_MOUSEWHEEL(WebBrowser::MFileDownload)
END_EVENT_TABLE()

WebBrowser::WebBrowser(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{

    wxColour col1, col2;
    col1.Set(wxT("Red"));
    col2.Set(wxT("Blue"));
    menubar = new wxMenuBar;
    fileMenu = new wxMenu;
    editMenu = new wxMenu;
    historyMenu = new wxMenu;
    lastTabs = new wxMenu;
    toolsMenu = new wxMenu;
    helpMenu = new wxMenu;
    karalama = new wxMenu;
    developerItem = new wxMenuItem(helpMenu, id_developer, wxT("developer"));
    kar = new wxMenuItem(karalama, ID_KARALAMA, wxT("karalama"));
    wxBitmap bm = wxBitmap("minibenbro-1.jpg");
    // bm.SetWidth(1);
    // bm.SetHeight(1);
    developerItem->SetBitmap(bm);

    newTab = new wxMenuItem(fileMenu, ID_NEWTAB, wxT("New Tab\tCtrl+T"));
    loadUrlVal= new wxMenuItem(fileMenu, ID_URL_AND_FILE_LOAD_ITEM, wxT("&Open\tCtrl+G"));
    quit = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit"));

ftpFileDownloadItem = new wxMenuItem(toolsMenu, id_ftp_file_download_item, wxT("Ftp File"));
    //editPageItem = new wxMenuItem(editMenu, id_editPageItem, wxT("Set page editable"));
    fileMenu->Append(newTab);
    fileMenu->Append(loadUrlVal);
    fileMenu->Append(quit);
    //editMenu->Append(editPageItem);
    editMenu->AppendCheckItem(id_editCheckItem, wxT("editCheckItem"), wxEmptyString);
    historyMenu->AppendSubMenu(lastTabs, wxT("Son Se&kmeler"));

    toolsMenu->Append(ftpFileDownloadItem);
    helpMenu->Append(developerItem);
    karalama->Append(kar);
    anyUrl = new wxURL(wxEmptyString);
    menubar->Append(fileMenu, wxT("&File"));
    menubar->Append(editMenu, wxT("&Edit"));
    menubar->Append(historyMenu, wxT("&Past"));
    menubar->Append(toolsMenu, wxT("Tools"));
    menubar->Append(helpMenu, wxT("&Help"));
    menubar->Append(karalama, wxT("karalama"));
    SetMenuBar(menubar);

    notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxNotebookNameStr);
    panel = new wxPanel(notebook);

    notebook->AddPage(panel, wxT("Page"), true, -1);


    //panel->SetBackgroundColour(col2);
    vbox = new wxBoxSizer(wxVERTICAL);

    toolbarhbox = new wxBoxSizer(wxHORIZONTAL);
    tctrl = new wxTextCtrl(panel, ID_URL_AND_FILE_LOAD_ITEM, wxT(""), wxPoint(-1, -1), wxSize(-1, -1));
    goButton = new wxButton(panel, ID_GO_BUTTON, wxT("Go"), wxPoint(-1, -1), wxSize(-1, -1));
    wview = wxWebView::New(panel, wxID_ANY, wxWebViewDefaultURLStr,
			   wxDefaultPosition, wxDefaultSize, wxWebViewBackendDefault, 0, wxWebViewNameStr);

    //wxFileName fn("./hello-wx.html");
    //htmlWin->LoadFile(fn);
    //htmlWin->SetBackgroundColour(col1);
    //htmlWin->LoadPage("https://www.google.com");
    toolbarhbox->Add(tctrl, 1, wxEXPAND | wxALL, 20);
    toolbarhbox->Add(goButton, 1, wxEXPAND | wxALL, 20);
    vbox->Add(toolbarhbox, 0, wxEXPAND | wxALL, 20);

    vbox->Add(wview, 1, wxEXPAND | wxALL, 20);
    panel->SetSizer(vbox);

    Connect(ID_NEWTAB, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::TabbedPages));

    Connect(ID_URL_AND_FILE_LOAD_ITEM, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));

    Connect(ID_URL_AND_FILE_LOAD_ITEM, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));

    Connect(ID_GO_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));
/*
    Connect(id_editPageItem, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::SetPageAsEditableFn));
*/
    Connect(id_editCheckItem, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::SetPageAsEditableFn));

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::OnQuit));

    Connect(ID_KARALAMA, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::Karalama));
    Connect(ID_WVIEW, wxEVT_COMMAND_WEBVIEW_ERROR,
            wxMouseEventHandler(WebBrowser::MFileDownload));

    Connect(id_ftp_file_download_item, wxEVT_COMMAND_MENU_SELECTED,
            wxMenuEventHandler(WebBrowser::FtpFileDownload));

/*
Connect(id_context_menu, wxEVT_COMMAND_MENU_SELECTED,
            wxContextMenuEventHandler(WebBrowser::MFileDownload));
            */
Connect(ID_WVIEW, wxEVT_COMMAND_WEBVIEW_NAVIGATED,
        wxWebViewEventHandler(WebBrowser::UrlHata));

Connect(ID_DOWNLOAD, wxEVT_COMMAND_MENU_SELECTED,
        wxContextMenuEventHandler(WebBrowser::DownloadRequest));

Connect(wview->GetId(), wxEVT_WEBVIEW_LOADED,
        wxWebViewEventHandler(WebBrowser::OnDocumentLoaded), NULL, this);

    wview->EnableContextMenu(true);

    Center();
}

void WebBrowser::TabbedPages(wxCommandEvent &WXUNUSED(event))
{
   // wxNotebook *parent;
    pnl = new wxPanel(notebook);
    wxBoxSizer *vbs = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbs = new wxBoxSizer(wxHORIZONTAL);
    newWebView = wxWebView::New(pnl, wxID_ANY, wxWebViewDefaultURLStr,
            wxDefaultPosition, wxDefaultSize, wxWebViewBackendDefault, 0,
            wxWebViewNameStr);
    newTextCtrl = new wxTextCtrl(pnl, ID_URL_AND_FILE_LOAD_ITEM_NEW, wxT(""), wxPoint(-1, -1), wxSize(-1, -1));
    newGoButton = new wxButton(pnl, ID_NEW_GO_BUTTON, wxT("new button"), wxPoint(-1, -1), wxSize(-1, -1));
    hbs->Add(newTextCtrl, 1, wxEXPAND | wxALL, 20);
    hbs->Add(newGoButton, 1, wxEXPAND | wxALL, 20);
    vbs->Add(hbs, 0, wxEXPAND | wxALL, 20);
    vbs->Add(newWebView, 1, wxEXPAND | wxALL, 20);

    pnl->SetSizer(vbs);

    Connect(ID_NEW_GO_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));
    Connect(ID_URL_AND_FILE_LOAD_ITEM_NEW, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));

    Connect(ID_URL_AND_FILE_LOAD_ITEM_NEW, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WebBrowser::FileAndUrlLoad));

    notebook->AddPage(pnl, wxT("Page"), true, -1);
}

void WebBrowser::SetTabWidgets()
{
    if (notebook->GetSelection() > 0) {
        panel = pnl;
        wview = newWebView;
        tctrl = newTextCtrl;
        goButton = newGoButton;
    }
    else {
        panel = panel;
        wview =wview;
        tctrl = tctrl;
        goButton = goButton;
    }
}

void WebBrowser::RunOnTabs(wxCommandEvent &WXUNUSED(event))
{
    int n = notebook->GetSelection();
    cout << n << endl;
}


void WebBrowser::FileAndUrlLoad(wxCommandEvent &WXUNUSED(event))
{
    //wxString urlVal = wxT("hellowxwb.html");
    /*
    if(notebook->GetSelection() > 0)
    {
        panel = pnl;
        wview = newWebView;
        // goButton = newGoButton;
    }

    else
    {
        panel = panel;
        wview = wview;
        // goButton = goButton;
    }
    */
    // wview = newWebView;
    // goButton = newGoButton;

    WebBrowser::GetFileAndURLFnctn();
    wview->LoadURL(urlAddress);
    wxString urlReg = urlAddress;

    vec_visited_pages->push_back(urlReg);

    lastTabs->Append(111, urlReg, "visited", true);

    if(wxEVT_COMMAND_WEBVIEW_ERROR)
        wxMessageBox("load hata", "baslik", wxOK);
}

wxString WebBrowser::GetFileAndURLFnctn()
{
    WebBrowser::SetTabWidgets();
    /*
    if(notebook->GetSelection() > 0)
    {
        panel = pnl;
        tctrl = newTextCtrl;
        goButton = newGoButton;
    }
    else
    {
        panel = panel;
        tctrl = tctrl;
        goButton = goButton;
    }
    */
    // tctrl = newTextCtrl;
    // goButton = newGoButton;
    urlAddress = tctrl->GetLineText(0);

    return urlAddress;
}

void WebBrowser::UrlHata(wxWebViewEvent &event)
{
    if(!anyUrl->IsOk())
        wxMessageBox("kek", "kek", wxOK);
}


void WebBrowser::FileDownload(wxContextMenuEvent &WXUNUSED(event))
{
    cout << "menu" << endl;
}


void WebBrowser::FtpFileDownload(wxMenuEvent &WXUNUSED(event))
{
//     wxWindow *winFtp = new wxWindow();
    wxDialog *ftpDialog = new wxDialog(window, wxID_ANY, "gtp",
            wxDefaultPosition, wxSize(200, 200), wxDEFAULT_DIALOG_STYLE, "dialog");
   // winFtp->SetSize(300, 300);
   // wxBoxSizer *ftpBoxSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl *ctrlUser, *ctrlPassword;
    ctrlUser = new wxTextCtrl(ftpDialog, wxID_ANY, wxT(""), wxPoint(20, 20),
            wxSize(-1, -1));
    ctrlPassword = new wxTextCtrl(ftpDialog, wxID_ANY, wxT(""), wxPoint(20, 60),
            wxSize(-1, -1));
    // ftpBoxSizer->Add(ctrlUser, 1, wxEXPAND | wxALL, 20);
    // ftpBoxSizer->Add(ctrlPassword, 1, wxEXPAND | wxALL, 20);
    // winFtp->SetSizer(ftpBoxSizer);
    // ftpDialog->SetSizer(ftpBoxSizer);
    ftpDialog->Show();
    //winFtp->Show();
    FILE *fileFtp;

    wxFTP ftp;
    ftp.SetUser("user");
    ftp.SetPassword("password");
    if(!ftp.Connect("ftp://ftp.wxwidgets.org"))
    {
        wxLogError("Could not connect");
        return;
    }

    ftp.ChDir("/pub/3.0.1");
    const char *ftpFileName = "wxwidgets-3.0.1.tar.bz2";
    int size = ftp.GetFileSize(ftpFileName);
    if(size == -1)
    {
        wxLogError("Couldn't get the file size for \"%s\"", ftpFileName);
    }

    wxInputStream *inFtp = ftp.GetInputStream(ftpFileName);
    if(!inFtp)
    {
        wxLogError("Couldn't get the file");
    }
    else
    {
        char *ftpData = new char[size];
        if(!inFtp->Read(ftpData, size))
        {
            wxLogError("Read error: %d", ftp.GetError());
        }
        else
        {
            fileFtp = fopen("ftpfile.txt", "w");
            // fwrite(ftpData, sizeof(char), sizeof(size),fileFtp);
            fprintf(fileFtp, "%s", ftpData);
            fflush(fileFtp);
fclose(fileFtp);
        }
        delete [] ftpData;
        delete inFtp;
    }

    ftp.Close();
    cout << "File download" << endl;
    ftpDialog->Hide();
}


void WebBrowser::FtpFileUpload(wxContextMenuEvent &WXUNUSED(event))
{
    // ....
    /*
    wxOutputStream *outFtp = ftp.GetOutputStream("ftpFileName");
    if(outFtp)
    {
        outFtp->Write("");
        delete outFtp;
    }
    */
}

void WebBrowser::MFileDownload(wxMouseEvent &event)
{
    wxMessageBox("tik", "Dosya yükleme işlemi henüz eklenmedi", wxOK);
}

void WebBrowser::SetPageAsEditableFn(wxCommandEvent &WXUNUSED(event))
{

    WebBrowser::SetTabWidgets();
    if (!wview->IsEditable()) {
        wview->SetEditable(true);
    }
    else
        wview->SetEditable(false);

    cout << "checked" << endl;
}

void WebBrowser::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}



void WebBrowser::Karalama(wxCommandEvent &WXUNUSED(event))
{
    cout << notebook->GetSelection() << endl;
};


void WebBrowser::DownloadRequest(wxContextMenuEvent &WXUNUSED(event))
{
    /*
    wxString fileName;
    fileName = wview->GetSelectedSource();
    FILE *fp;
    fp = fopen(fileName, "w");
    fclose(fp);
    printf("%s\n", fileName);
    */
}


void WebBrowser::OnDocumentLoaded(wxWebViewEvent& event)
{
    /*
    if(event.GetURL() == wview->GetCurrentURL())
    {
        wxLogMessage("%s", "Document loaded; url='" + event.GetURL() + "'");
    }
    // UpdateState();
    */
}

