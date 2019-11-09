#include "panel.h"
#include <wx/stdpaths.h>

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
}

CPanel::~CPanel()
{
}

bool CPanel::SaveXmlFileFromList(wxXmlNode* mail)
{
    long itemIndex = -1;
    while((itemIndex = m_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND) {
        wxListItem item;
        item.SetId(itemIndex);
        item.SetMask(wxLIST_MASK_TEXT);

        item.SetColumn(0);
        m_listCtrl->GetItem(item);
        wxXmlNode* node = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, item.GetText());

        for(int col = 1; col < m_listCtrl->GetColumnCount(); col++) {
            item.SetColumn(col);
            m_listCtrl->GetItem(item);
            wxString itemColumm = item.GetText();
            m_listCtrl->GetColumn(col, item);
            wxString labelColumm = item.GetText();

            node->AddAttribute(labelColumm, itemColumm);
        }
        mail->AddChild(node);
    }

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
    return arrayString;
}
