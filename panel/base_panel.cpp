#include "base_panel.h"
#include <map>
#include <vector>

CBasePanel::CBasePanel(wxWindow* window, wxString namePage)
    : wxPanel(window, NewControlId())
{
    m_namePage = namePage;
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.page, &CBasePanel::ReadPageXml));
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.web, &CBasePanel::ReadWebXml));

    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.namePage, &CBasePanel::WriteAttributeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.widthCol, &CBasePanel::WriteAttributeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.heightRow, &CBasePanel::WriteAttributeXml));

    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeTable.webSite, &CBasePanel::WriteAttributeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeTable.login, &CBasePanel::WriteAttributeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeTable.password, &CBasePanel::WriteAttributeXml));

    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.web, &CBasePanel::CreateNodeXml));

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

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_string = *itr;

        for(auto& p : m_listWriteXml) {
            if(node != nullptr && t_string == p.first) {
                TAttributeParseXml attr{ mail, node, p.first, itr, count_web };
                (this->*p.second)(attr);
            }
        }
    }

    return true;
}

void CBasePanel::CreateNodeXml(TAttributeParseXml& attr)
{
    wxString temp = wxString::Format(wxT("%s%d"), attr.attributeName, attr.count++);
    attr.child = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
    attr.parent->AddChild(attr.child);
}

void CBasePanel::WriteAttributeXml(TAttributeParseXml& attr)
{
    attr.child->AddAttribute(attr.attributeName, *(++attr.itrAttributeValue));
}
