#include "base_panel.h"
#include <vector>

CBasePanel::CBasePanel(wxWindow* window)
    : wxPanel(window, NewControlId())
{
    m_attributeUser.push_back(m_attributeTable.login);
    m_attributeUser.push_back(m_attributeTable.password);
}

CBasePanel::~CBasePanel()
{
}

void CBasePanel::LoadXmlFileInList(wxXmlNode* node)
{
    while(node != nullptr) {

        if(node->GetName().Find(m_attributeXml.page) != -1) {
            m_namePage = node->GetAttribute(m_attributeXml.namePage);
        }

        if(node->GetName().Find(m_attributeXml.web) != -1) {
            wxArrayString arrayString;
            arrayString.Add(m_attributeTable.webSite);
            arrayString.Add(node->GetAttribute(m_attributeTable.webSite, m_attributeXml.notFound));
            arrayString.Add(m_attributeTable.login);
            arrayString.Add(node->GetAttribute(m_attributeTable.login, m_attributeXml.notFound));
            arrayString.Add(m_attributeTable.password);
            arrayString.Add(node->GetAttribute(m_attributeTable.password, m_attributeXml.notFound));
            SetValue(arrayString);
        }

        if(node->GetChildren() != nullptr)
            node = node->GetChildren();
        else
            node = node->GetNext();
    }
}

bool CBasePanel::SaveXmlFileFromList(wxXmlNode* mail)
{
    int num_col = 0;
    int num_row = 0;
    int count_web = 0;

    wxArrayString arrayString;
    wxXmlNode* node = nullptr;

    GetValue(arrayString);

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_string = *itr;

        if(mail != nullptr && t_string == m_attributeXml.namePage) {
            mail->AddAttribute(m_attributeXml.namePage, *(++itr));
        }

        wxString t_col = wxString::Format(wxT("%s%d"), m_attributeXml.widthCol, num_col);
        if(mail != nullptr && t_string == t_col) {
            mail->AddAttribute(t_col, *(++itr));
            num_col++;
        }

        wxString t_row = wxString::Format(wxT("%s%d"), m_attributeXml.heightRow, num_row);
        if(mail != nullptr && t_string == t_row) {
            mail->AddAttribute(t_row, *(++itr));
            num_row++;
        }

        if(t_string == m_attributeTable.webSite) {
            wxString temp = wxString::Format(wxT("%s%d"), m_attributeXml.web, count_web++);
            node = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
            node->AddAttribute(m_attributeTable.webSite, *(++itr));
            mail->AddChild(node);
        }

        for(auto& p : m_attributeUser)
            if(node != nullptr && t_string == p)
                node->AddAttribute(p, *(++itr));
    }

    return true;
}