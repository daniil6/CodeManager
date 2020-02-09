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
        wxArrayString arrayString;

        arrayString.Add(m_attribute.webSite);
        arrayString.Add(node->GetAttribute(m_attribute.webSite, wxT("NOT_FOUND")));
        arrayString.Add(m_attribute.login);
        arrayString.Add(node->GetAttribute(m_attribute.login, wxT("NOT_FOUND")));
        arrayString.Add(m_attribute.password);
        arrayString.Add(node->GetAttribute(m_attribute.password, wxT("NOT_FOUND")));

        SetValue(arrayString);

        if(node->GetChildren() != nullptr)
            node = node->GetChildren();
        else
            node = node->GetNext();
    }
}

bool CBasePanel::SaveXmlFileFromList(wxXmlNode* mail)
{
    wxXmlNode* node = nullptr;
    wxArrayString arrayString;
    GetValue(arrayString);

    int count_web = 0;
    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_string = *itr;
        if(t_string == m_attribute.webSite && mail != nullptr) {
            t_string = *(++itr);
            if(t_string != m_attribute.mail) {
                wxString temp = wxString::Format(wxT("%s%d"), m_attribute.web, count_web++);
                node = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
                node->AddAttribute(m_attribute.webSite, t_string);
                mail->AddChild(node);
            } else
                node = mail;
        }
        if(node != nullptr && t_string == m_attribute.login)
            node->AddAttribute(t_string, *(++itr));
        if(node != nullptr && t_string == m_attribute.password)
            node->AddAttribute(t_string, *(++itr));
    }

    return true;
}