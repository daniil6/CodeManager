#include "MainFrame.h"

#define WIDTH 500
#define HEIGHT 500

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("CodeManager"))
{
    SetIcon(wxICON(lock));

    m_choicebook = new wxListbook(this, NewControlId(), wxDefaultPosition, wxDefaultSize);

    CreateMenuBar();

    wxBoxSizer* mainBox = new wxBoxSizer(wxHORIZONTAL);
    mainBox->Add(m_choicebook, 1, wxEXPAND);

    LoadXml();

    this->SetSizerAndFit(mainBox);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::LoadXml()
{
    wxXmlDocument xmlDoc;
    bool resLoad = true;
    if(xmlDoc.Load(NAMEFILEXML) == false)
        resLoad = false;
    if(resLoad == true) {
        wxXmlNode* root = xmlDoc.GetRoot();
        if(root->GetName() != "root")
            resLoad = false;

        if(resLoad == true) {
            wxXmlNode* mail = root->GetChildren();
            while(mail != nullptr) {
                wxString nameMail = mail->GetName();
                CPanel* panel = new CPanel(m_choicebook, nameMail);
                m_choicebook->AddPage(panel, nameMail);
                panel->LoadXmlFileInList(mail);
                mail = mail->GetNext();
            }
        }
    }
}

void CMainFrame::OnSaveXml(wxCommandEvent& event)
{
    wxXmlDocument xmlDoc;
    wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, ROOTXML);
    xmlDoc.SetRoot(root);
    for(unsigned int page = 0; page < m_choicebook->GetPageCount(); page++) {
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
    // xmlDoc.Save("output.xml");
    xmlDoc.Save(NAMEFILEXML);
}

void CMainFrame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* file = new wxMenu;
    wxMenu* edit = new wxMenu;

    wxMenuItem* save = new wxMenuItem(file, NewControlId(), wxT("Save"));
    file->Append(save);

    wxMenuItem* addNewItem = new wxMenuItem(edit, NewControlId(), wxT("Add new item"));
    wxMenuItem* deleteItem = new wxMenuItem(edit, NewControlId(), wxT("Delete item"));
    edit->Append(addNewItem);
    edit->Append(deleteItem);

    menuBar->Append(file, wxT("File"));
    menuBar->Append(edit, wxT("Edit"));

    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnSaveXml, this, save->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnAddNewItem, this, addNewItem->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnDeleteItem, this, deleteItem->GetId());
    SetMenuBar(menuBar);
}

void CMainFrame::OnAddNewItem(wxCommandEvent& event)
{
    wxWindow* windowPage = m_choicebook->GetPage(m_choicebook->GetSelection());
    if(windowPage != nullptr) {
        CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
        if(panelPage != nullptr)
            panelPage->AddNewItem();
    }
}

void CMainFrame::OnDeleteItem(wxCommandEvent& event)
{
    wxWindow* windowPage = m_choicebook->GetPage(m_choicebook->GetSelection());
    if(windowPage != nullptr) {
        CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
        if(panelPage != nullptr)
            panelPage->DeleteItem();
    }
}
