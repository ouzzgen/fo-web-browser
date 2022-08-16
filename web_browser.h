#ifndef WEB_BROWSER_H
#define WEB_BROWSER_H value

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/protocol/ftp.h>
#include <wx/wxprec.h>
#include <wx/window.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/html/htmlwin.h>
#include <wx/webview.h>
#include <wx/event.h>
#include <wx/url.h>

using namespace std;

class WebBrowser : public wxFrame
{
    public:
        WebBrowser(const wxString &title);
        wxWindow *mainWin;
        wxWindow *window;
        wxNotebook *notebook;
        wxMenuBar *menubar;
        wxMenu *fileMenu;
        wxMenu *editMenu;
        wxMenu *historyMenu;
        wxMenu *lastTabs;
        wxMenu *toolsMenu;
        wxMenu *helpMenu;
        wxMenu *karalama;
        wxMenuItem *developerItem;
        wxMenuItem *kar;
        wxPanel *panel, *pnl;
        wxBoxSizer *vbox, *toolbarhbox;


        wxTextCtrl *tctrl, *newTextCtrl;
        wxWebView *wview, *newWebView;
        wxButton *goButton, *newGoButton;


        wxURL *anyUrl;

        wxMenuItem *newTab, *loadUrlVal, *editPageItem, *cutItem, *copyItem, *pasteItem, *ftpFileDownloadItem;
        wxMenuItem *quit;

        wxString urlAddress;


        void FileAndUrlLoad(wxCommandEvent &event);
        void FileDownload(wxContextMenuEvent &event);
        void FtpFileDownload(wxMenuEvent &event);
        void FtpFileUpload(wxContextMenuEvent &event);
        wxString GetFileAndURLFnctn();
        void TabbedPages(wxCommandEvent &event);
        void SetTabWidgets();
        void RunOnTabs(wxCommandEvent &event);
        void SetPageAsEditableFn(wxCommandEvent &event);

        void UrlHata(wxWebViewEvent &event);
        void MFileDownload(wxMouseEvent &event);
        void OnQuit(wxCommandEvent &event);

        void DownloadRequest(wxContextMenuEvent &event);
        void OnDocumentLoaded(wxWebViewEvent &event);

        void Karalama(wxCommandEvent &event);

        const int ID_TOOLS_MENU = 10;
        const int ID_WVIEW= 1;
        const int ID_URL_AND_FILE_LOAD_ITEM = 2;
        const int ID_GO_BUTTON = 3;
        const int ID_NEWTAB = 4;
        const int ID_LAST_TABS = 5;
        const int ID_NEW_GO_BUTTON = 6;
        const int ID_URL_AND_FILE_LOAD_ITEM_NEW = 7;
        const int id_ftp_file_download_item = 35;

        const int ID_DOWNLOAD = 9;

        const int id_editPageItem = 20;
        const int id_editCheckItem = 21;
        const int ID_KARALAMA = 29;
        const int id_context_menu = 30;
        const int id_developer = 99;
        std::vector<wxString> *vec_visited_pages;

    private :
        DECLARE_EVENT_TABLE();
};



#endif

