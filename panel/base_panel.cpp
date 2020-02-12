#include "base_panel.h"
#include <vector>

CBasePanel::CBasePanel(wxWindow* window)
    : wxPanel(window, NewControlId())
{
}

CBasePanel::~CBasePanel()
{
}

void CBasePanel::LoadXmlFileInList(wxXmlNode* node)
{
    while(node != nullptr) {

        if(node->GetName().Find(m_attribute.page) != -1) {
            m_namePage = node->GetAttribute(m_attribute.namePage);
        }

        if(node->GetName().Find(m_attribute.web) != -1) {
            wxArrayString arrayString;
            arrayString.Add(m_attribute.webSite);
            arrayString.Add(node->GetAttribute(m_attribute.webSite, m_attribute.notFound));
            arrayString.Add(m_attribute.login);
            arrayString.Add(node->GetAttribute(m_attribute.login, m_attribute.notFound));
            arrayString.Add(m_attribute.password);
            arrayString.Add(node->GetAttribute(m_attribute.password, m_attribute.notFound));
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

        if(mail != nullptr && t_string == m_attribute.namePage) {
            mail->AddAttribute(m_attribute.namePage, *(++itr));
        }

        wxString t_col = wxString::Format(wxT("%s%d"), m_attribute.widthCol, num_col);
        if(mail != nullptr && t_string == t_col) {
            mail->AddAttribute(t_col, *(++itr));
            num_col++;
        }

        wxString t_row = wxString::Format(wxT("%s%d"), m_attribute.heightRow, num_row);
        if(mail != nullptr && t_string == t_row) {
            mail->AddAttribute(t_row, *(++itr));
            num_row++;
        }

        if(t_string == m_attribute.webSite) {
            wxString temp = wxString::Format(wxT("%s%d"), m_attribute.web, count_web++);
            node = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
            node->AddAttribute(m_attribute.webSite, *(++itr));
            mail->AddChild(node);
        }

        if(node != nullptr && t_string == m_attribute.login)
            node->AddAttribute(m_attribute.login, *(++itr));
        if(node != nullptr && t_string == m_attribute.password)
            node->AddAttribute(m_attribute.password, *(++itr));
    }

    return true;
}