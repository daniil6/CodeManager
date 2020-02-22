#include "MainFrame.h"

#define WIDTH 500
#define HEIGHT 500

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("Code Manager"))
{
    SetIcon(wxICON(lock));

    m_choicebook = new wxListbook(this, NewControlId());

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
                wxString nameMail = mail->GetAttribute(wxT("NamePage"));
                CPanel* panel = new CPanel(m_choicebook, nameMail);
                panel->LoadXmlFileInList(mail);
                m_choicebook->AddPage(panel, nameMail);
                mail = mail->GetNext();
            }
        }
    }

    ResizePageInListbook();
}

template <typename TReturn, typename TClass, typename... TParam>
TReturn CMainFrame::GetClassMethod(int numPage, TReturn (TClass::*func)(TParam...), TParam... param)
{
    if(m_choicebook->GetPageCount() != 0) {
        wxWindow* windowPage = m_choicebook->GetPage(numPage);
        if(windowPage != nullptr) {
            TClass* panelPage = dynamic_cast<TClass*>(windowPage);
            if(panelPage != nullptr && func != nullptr)
                return (panelPage->*func)(param...);
            else
                return nullptr;
        } else
            return nullptr;
    } else
        return nullptr;
}

#include "panel/xmlparsetest.h"

void CMainFrame::OnSaveXml(wxCommandEvent& event)
{
    wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("root"));

    int countPage = m_choicebook->GetPageCount();
    for(int page = 0; page < countPage; page++) {

        wxXmlNode* nodePage = GetClassMethod(page, &CPanel::SaveXmlFileFromList, page);
        root->AddChild(nodePage);
    }

    CXmlParseTest::CloseXmlFile(root, "output.xml");
    // CXmlParseTest::CloseXmlFile(root, NAMEFILEXML);
}

void CMainFrame::ResizePageInListbook()
{
    wxArrayInt arraySizeCol;

    for(unsigned int page = 0; page < m_choicebook->GetPageCount(); page++) {
        wxWindow* windowPage = m_choicebook->GetPage(page);
        if(windowPage != nullptr) {
            CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
            if(panelPage != nullptr) {
                wxArrayInt new_arraySizeCol;
                panelPage->GetSizeAllColumn(new_arraySizeCol);
                if(new_arraySizeCol.size() == arraySizeCol.size()) {
                    for(unsigned int i = 0; i < new_arraySizeCol.size(); i++)
                        if(arraySizeCol[i] < new_arraySizeCol[i])
                            arraySizeCol[i] = new_arraySizeCol[i];
                } else
                    arraySizeCol = new_arraySizeCol;
            }
        }
    }

    for(unsigned int page = 0; page < m_choicebook->GetPageCount(); page++) {
        wxWindow* windowPage = m_choicebook->GetPage(page);
        if(windowPage != nullptr) {
            CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
            if(panelPage != nullptr)
                panelPage->SetSizeAllColumn(arraySizeCol);
        }
    }
}

void CMainFrame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* file = new wxMenu;
    wxMenu* edit = new wxMenu;

    wxMenuItem* save = new wxMenuItem(file, NewControlId(), wxT("Save"));
    file->Append(save);

    wxMenuItem* addPage = new wxMenuItem(edit, NewControlId(), wxT("Add Page"));
    wxMenuItem* deletePage = new wxMenuItem(edit, NewControlId(), wxT("Delete Page"));
    wxMenuItem* addNewItem = new wxMenuItem(edit, NewControlId(), wxT("Add new item"));
    wxMenuItem* deleteItem = new wxMenuItem(edit, NewControlId(), wxT("Delete item"));

    edit->Append(addPage);
    edit->Append(addNewItem);
    edit->AppendSeparator();
    edit->Append(deletePage);
    edit->Append(deleteItem);

    menuBar->Append(file, wxT("File"));
    menuBar->Append(edit, wxT("Edit"));

    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnSaveXml, this, save->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnAddPage, this, addPage->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnDeletePage, this, deletePage->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnAddNewItem, this, addNewItem->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::OnDeleteItem, this, deleteItem->GetId());

    SetMenuBar(menuBar);
}

void CMainFrame::OnAddNewItem(wxCommandEvent& event)
{
    if(m_choicebook->GetPageCount() != 0) {
        wxWindow* windowPage = m_choicebook->GetPage(m_choicebook->GetSelection());
        if(windowPage != nullptr) {
            CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
            if(panelPage != nullptr)
                panelPage->AddNewItem();
        }
    }
}

void CMainFrame::OnDeleteItem(wxCommandEvent& event)
{
    if(m_choicebook->GetPageCount() != 0) {
        int selected = m_choicebook->GetSelection();
        if(selected != -1) {
            wxWindow* windowPage = m_choicebook->GetPage(selected);
            if(windowPage != nullptr) {
                CPanel* panelPage = dynamic_cast<CPanel*>(windowPage);
                if(panelPage != nullptr)
                    panelPage->DeleteItem();
            }
        } else
            wxMessageBox(wxT("Select item"));
    } else
        wxMessageBox(wxT("No table for delete item"));
}

void CMainFrame::OnAddPage(wxCommandEvent& event)
{
    wxTextEntryDialog dlg(this, wxT("Enter name page"), wxT("Name new page"));
    if(dlg.ShowModal() == wxID_OK) {
        wxString name = dlg.GetValue();
        m_choicebook->AddPage(new CPanel(m_choicebook, name), name);
    }
}

void CMainFrame::OnDeletePage(wxCommandEvent& event)
{
    if(m_choicebook->GetPageCount() != 0) {
        int selected = m_choicebook->GetSelection();
        if(selected != -1) {
            wxMessageDialog dlg(this, wxT("Delete page"), wxT("Delete page?"), wxOK | wxCANCEL);
            if(dlg.ShowModal() == wxID_OK)
                m_choicebook->DeletePage(selected);
        } else
            wxMessageBox(wxT("Select page"));
    } else
        wxMessageBox(wxT("No page for delete"));
}