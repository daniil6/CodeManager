#include "MainFrame.h"

#define WIDTH 300
#define HEIGHT 170

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("Code Manager"))
{
    SetIcon(wxICON(lock));

    m_choicebook = new wxListbook(this, NewControlId());
    m_txtFind = new wxTextCtrl(this, NewControlId(), wxT(""));

    CreateMenuBar();

    wxBoxSizer* mainBox = new wxBoxSizer(wxVERTICAL);
    mainBox->Add(m_txtFind, 0, wxEXPAND);
    mainBox->Add(m_choicebook, 1, wxEXPAND);

    this->SetSizerAndFit(mainBox);

    LoadXml();

    Bind(wxEVT_TEXT, &CMainFrame::OnEditTxtFind, this, m_txtFind->GetId());
}

void CMainFrame::OnEditTxtFind(wxCommandEvent& event)
{
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::LoadXml()
{
    wxXmlDocument xmlDoc;
    wxXmlNode* page = TXmlParse<CXmlCodeManager, TAttributeParseXml>::Open(xmlDoc, NAMEFILEXML);
    if(page != nullptr) {
        while(page != nullptr) {
            wxString nameMail = page->GetAttribute(wxT("NamePage"));
            CPanel* panel = new CPanel(m_choicebook, nameMail);
            panel->Load(page);
            m_choicebook->AddPage(panel, nameMail);
            page = page->GetNext();
        }
        ResizePageInListbook();
    } else
        this->SetSize(wxSize(WIDTH, HEIGHT));
}

template <typename TReturn, typename TClass, typename... TParam>
TReturn CMainFrame::GetClassMethod(int numPage, TReturn (TClass::*func)(TParam...), TReturn error, TParam&&... param)
{
    if(m_choicebook->GetPageCount() != 0) {
        wxWindow* windowPage = m_choicebook->GetPage(numPage);
        if(windowPage != nullptr) {
            TClass* panelPage = dynamic_cast<TClass*>(windowPage);
            if(panelPage != nullptr && func != nullptr)
                return (panelPage->*func)(param...);
            else
                return error;
        } else
            return error;
    } else
        return error;
}

void CMainFrame::OnAddNewItem(wxCommandEvent& event)
{
    GetClassMethod(m_choicebook->GetSelection(), &CPanel::AddNewItem, false);
}

void CMainFrame::OnSaveXml(wxCommandEvent& event)
{
    wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("root"));

    int countPage = m_choicebook->GetPageCount();
    for(int page = 0; page < countPage; page++) {
        wxXmlNode* nodePage = GetClassMethod(page, &CPanel::Save, (wxXmlNode*)nullptr, (int)page);
        root->AddChild(nodePage);
    }

    // TXmlParse<CXmlCodeManager, TAttributeParseXml>::Close(root);
    TXmlParse<CXmlCodeManager, TAttributeParseXml>::Close(root, NAMEFILEXML);
}

void CMainFrame::ResizePageInListbook()
{
    wxArrayInt arraySizeCol;

    int pageCount = m_choicebook->GetPageCount();
    for(int page = 0; page < pageCount; page++) {

        wxArrayInt new_arraySizeCol;
        GetClassMethod(page, &CPanel::GetSizeAllColumn, false, new_arraySizeCol);

        if(new_arraySizeCol.size() == arraySizeCol.size()) {
            for(unsigned int i = 0; i < new_arraySizeCol.size(); i++)
                if(arraySizeCol[i] < new_arraySizeCol[i])
                    arraySizeCol[i] = new_arraySizeCol[i];
        } else
            arraySizeCol = new_arraySizeCol;
    }

    for(int page = 0; page < pageCount; page++)
        GetClassMethod(page, &CPanel::SetSizeAllColumn, false, *(const_cast<const wxArrayInt*>(&arraySizeCol)));
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

void CMainFrame::OnDeleteItem(wxCommandEvent& event)
{
    if(m_choicebook->GetPageCount() != 0) {
        int selected = m_choicebook->GetSelection();
        if(selected != -1)
            GetClassMethod(selected, &CPanel::DeleteItem, false);
        else
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
            wxString namePage = m_choicebook->GetPageText(selected);
            wxMessageDialog dlg(this, wxT("Delete page ") + namePage, wxT("Delete page?"), wxOK | wxCANCEL);
            if(dlg.ShowModal() == wxID_OK)
                m_choicebook->DeletePage(selected);
        } else
            wxMessageBox(wxT("Select page"));
    } else
        wxMessageBox(wxT("No page for delete"));
}