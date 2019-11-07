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

    bool resLoad = true;
    if(!m_doc.Load(NAMEFILEXML))
        resLoad = false;
    wxXmlNode* root = m_doc.GetRoot();
    if(root->GetName() != "root")
        resLoad = false;

    if(resLoad == true) {
        wxXmlNode* mail = root.GetChildren();
        while(mail != nullptr) {
            wxString nameMail = mail->GetName();
            CPanel* panel = new CPanel(m_choicebook, nameMail, m_doc);
            m_choicebook->AddPage(panel, nameMail);
            panel->LoadXmlFileInList(mail->GetChildren());
            mail = mail->GetNext();
        }
    }

    
    
    
    wxXmlDocument docClose;
    wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, ROOTXML);
    docClose->SetRoot(root);
    
    
    //docClose->Save(NAMEFILEXML, wxXML_NO_INDENTATION);
    if(mail != nullptr) {
        for(int page = 0; page < m_choicebook->GetPageCount(); page++) {
            wxWindow* windowPage = m_choicebook->GetPage(page);
            if(windowPage != nullptr) {
                CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
                if(panelPage != nullptr) {
                    wxstring z = m_choicebook->GetPageText(page);
                    wxXmlNode* mail = new wxXmlNode(root, wxXML_ELEMENT_NODE, z);
                    root.AddChild(mail);
                    panelPage->SaveXmlFileFromList(mail->GetChildren());
                }
            }
        }
    }

    // m_choicebook->AddPage(new CPanel(m_choicebook, wxT("mail 2"), m_doc), wxT("mail 2"));
    // m_choicebook->AddPage(new CPanel(m_choicebook, wxT("mail 3"), m_doc), wxT("mail 3"));

    // const std::vector<wxString> allow{ wxT("web1"), wxT("name"), wxT("pas") };
    // wxArrayString arrayString(allow.size(), &allow.front());
    //
    // for(unsigned i = 0; i < m_choicebook->GetPageCount(); i++) {
    //}
    //
    // wxWindow* windowPage = m_choicebook->GetPage(1);
    // if(windowPage != nullptr) {
    //    CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
    //    if(panelPage != nullptr) {
    //        panelPage->SetValue(arrayString);
    //        // panelPage->SaveXmlFileFromList();
    //        panelPage->LoadXmlFileInList();
    //    }
    //}
    // m_doc.Save(NAMEFILEXML, wxXML_NO_INDENTATION);

    this->SetSizerAndFit(mainBox);
}

CMainFrame::~CMainFrame()
{
}
