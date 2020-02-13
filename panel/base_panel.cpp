#include "base_panel.h"
#include <map>
#include <vector>

CBasePanel::CBasePanel(wxWindow* window)
    : wxPanel(window, NewControlId())
{
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.page, &CBasePanel::ReadPageXml));
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.web, &CBasePanel::ReadWebXml));

    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.namePage, &CBasePanel::WritePageXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.widthCol, &CBasePanel::WriteColSizeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.heightRow, &CBasePanel::WriteRowSizeXml));

    m_attributeUser.push_back(m_attributeTable.webSite);
    m_attributeUser.push_back(m_attributeTable.login);
    m_attributeUser.push_back(m_attributeTable.password);
}

CBasePanel::~CBasePanel()
{
}

void CBasePanel::LoadXmlFileInList(wxXmlNode* node)
{
    while(node != nullptr) {

        for(auto& p : m_listReadXml)
            if(node->GetName().Find(p.first) != -1)
                (this->*p.second)(node);

        if(node->GetChildren() != nullptr)
            node = node->GetChildren();
        else
            node = node->GetNext();
    }
}

void CBasePanel::ReadPageXml(wxXmlNode* node)
{
    m_namePage = node->GetAttribute(m_attributeXml.namePage);
}

void CBasePanel::ReadWebXml(wxXmlNode* node)
{
    wxArrayString arrayString;
    for(auto& p : m_attributeUser) {
        arrayString.Add(p);
        arrayString.Add(node->GetAttribute(p, m_attributeXml.notFound));
    }
    SetValue(arrayString);
}

bool CBasePanel::SaveXmlFileFromList(wxXmlNode* mail)
{
    int count_web = 0;

    wxArrayString arrayString;
    wxXmlNode* node = mail;

    GetValue(arrayString);

    arrayString.push_back(wxT("TestAttribute"));
    arrayString.push_back(wxT("TestValue"));

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_string = *itr;

        for(auto& p : m_listWriteXml)
            if(node != nullptr && t_string == p.first)
                (this->*p.second)(node, *(++itr));

        if(t_string == wxT("Next")) {
            wxString temp = wxString::Format(wxT("%s%d"), m_attributeXml.web, count_web++);
            node = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
            mail->AddChild(node);
        }

        for(auto& p : m_attributeUser)
            if(node != nullptr && t_string == p)
                node->AddAttribute(p, *(++itr));
    }

    return true;
}

void CBasePanel::WriteAttributeXml(wxXmlNode* node, wxString attributeName, wxString attributeValue)
{
    node->AddAttribute(attributeName, attributeValue);
}

void CBasePanel::WritePageXml(wxXmlNode* node, wxString attribute)
{
    node->AddAttribute(m_attributeXml.namePage, attribute);
}

void CBasePanel::WriteColSizeXml(wxXmlNode* node, wxString attribute)
{
    node->AddAttribute(m_attributeXml.widthCol, attribute);
}

void CBasePanel::WriteRowSizeXml(wxXmlNode* node, wxString attribute)
{
    node->AddAttribute(m_attributeXml.heightRow, attribute);
}
