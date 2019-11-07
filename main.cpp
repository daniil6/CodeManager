#include "MainFrame.h"
class wxMiniApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit()
{
    CMainFrame* mainFrame = new CMainFrame;
    mainFrame->Show();
    return true;
}
