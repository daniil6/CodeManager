#include "panel.h"
#include <wx/stdpaths.h>

#define ROOTXML wxT("root")

CPanel::CPanel(wxWindow* window, wxString namePanel, wxXmlDocument& doc)
    : wxPanel(window, NewControlId())
    , m_namePanel(namePanel)
    , m_doc(doc)
{
    m_listCtrl = new wxListCtrl(this, NewControlId(), wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    m_listCtrl->InsertColumn(0, attribute.webSite);
    m_listCtrl->InsertColumn(1, attribute.login);
    m_listCtrl->InsertColumn(2, attribute.password);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_listCtrl, 1, wxEXPAND);
    this->SetSizerAndFit(h_box);

    // wxXmlNode* root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, ROOTXML);
    // m_doc->SetRoot(root);
    // m_doc->Save(NAMEFILEXML, wxXML_NO_INDENTATION);
}

CPanel::~CPanel()
{
}

bool CPanel::SaveXmlFileFromList()
{
    if(!m_doc.Load(NAMEFILEXML, wxT("UTF-8"), wxXML_ELEMENT_NODE))
        return false;
    // start processing the XML file
    wxXmlNode* root = m_doc.GetRoot();
    if(root->GetName() != "root")
        return false;

    long itemIndex = -1;
    while((itemIndex = m_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND) {
        wxXmlNode* mail = new wxXmlNode(root, wxXML_ELEMENT_NODE, m_namePanel);
        wxListItem item;
        item.SetId(itemIndex);
        item.SetMask(wxLIST_MASK_TEXT);
        for(int col = 0; col < m_listCtrl->GetColumnCount(); col++) {
            item.SetColumn(col);
            m_listCtrl->GetItem(item);
            mail->AddAttribute(item.GetText(), m_listCtrl->GetItemText(itemIndex, col));
        }
        root->AddChild(mail);
    }

    // examine prologue
    // wxXmlNode* prolog = m_doc->GetDocumentNode()->GetChildren();
    // while(prolog) {
    //    if(prolog->GetType() == wxXML_PI_NODE && prolog->GetName() == "target") {
    //        // process Process Instruction contents
    //        wxString pi = prolog->GetContent();
    //    }
    //}
    return true;
}

void CPanel::LoadXmlFileInList(wxXmlNode* node)
{
    while(node != nullptr) {
        wxArrayString arrayString;
        arrayString.Add(node->GetName());
        arrayString.Add(node->GetAttribute(attribute.login, wxT("NOT_FOUND")));
        arrayString.Add(node->GetAttribute(attribute.password, wxT("NOT_FOUND")));
        SetValue(arrayString);
        node = node->GetNext();
    }
}

void CPanel::SetValue(const wxArrayString& arrayString)
{
    int i = 0;
    auto itr = arrayString.begin();
    long itemIndex = m_listCtrl->InsertItem(0, *itr);

    while(++itr != arrayString.end())
        m_listCtrl->SetItem(itemIndex, ++i, *itr);
}

wxArrayString CPanel::GetValue()
{
    wxArrayString arrayString;
    long itemIndex = -1;
    while((itemIndex = m_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND) {
        for(int col = 0; col < m_listCtrl->GetColumnCount(); col++) {
            arrayString.Add(m_listCtrl->GetItemText(itemIndex, col));
        }
    }
}
