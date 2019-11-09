#include "MainFrame.h"
#include <wx/listbook.h>

#define WIDTH 500
#define HEIGHT 500

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("CodeManager"))
{
    SetIcon(wxICON(lock));

    wxListbook* m_choicebook = new wxListbook(this, NewControlId(), wxDefaultPosition, wxDefaultSize);

    wxBoxSizer* mainBox = new wxBoxSizer(wxHORIZONTAL);
    mainBox->Add(m_choicebook, 1, wxEXPAND);


    // load xml file
    bool resLoad = true;
    if(m_xmlDocument.Load(NAMEFILEXML) == false)
        resLoad = false;
    if(resLoad == true) {
        wxXmlNode* root = m_xmlDocument.GetRoot();
        if(root->GetName() != "root")
            resLoad = false;

        if(resLoad == true) {
            wxXmlNode* mail = root->GetChildren();
            while(mail != nullptr) {
                wxString nameMail = mail->GetName();
                CPanel* panel = new CPanel(m_choicebook, nameMail, m_xmlDocument);
                m_choicebook->AddPage(panel, nameMail);
                panel->LoadXmlFileInList(mail->GetChildren());
                mail = mail->GetNext();
            }
        }
    }


    // save xml file
    wxXmlDocument closeXmlDocument;
    wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, ROOTXML);
    closeXmlDocument.SetRoot(root);
    for(int page = 0; page < m_choicebook->GetPageCount(); page++) {
        wxWindow* windowPage = m_choicebook->GetPage(page);
        if(windowPage != nullptr) {
            CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
            if(panelPage != nullptr) {
                wxString namePage = m_choicebook->GetPageText(page);
                wxXmlNode* nodePage = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, namePage);
                panelPage->SaveXmlFileFromList(nodePage);
                root->AddChild(nodePage);
            }
        }
    }
    closeXmlDocument.Save("output.xml");

    this->SetSizerAndFit(mainBox);
}

CMainFrame::~CMainFrame()
{
}
