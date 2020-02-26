#include "xmlcodemanager.h"

CXmlCodeManager::CXmlCodeManager(wxWindow* window, wxString namePage)
    : CBasePanel(window, namePage)
{
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.page, &CXmlCodeManager::ReadPageXml));
    m_listReadXml.insert(std::pair<wxString, ifuncRead>(m_attributeXml.web, &CXmlCodeManager::ReadWebXml));

    m_listWriteXml.insert(
        std::pair<wxString, ifuncWrite>(m_attributeXml.namePage, &CXmlCodeManager::WriteAttributeXml));
    m_listWriteXml.insert(
        std::pair<wxString, ifuncWrite>(m_attributeXml.widthCol, &CXmlCodeManager::WriteAttributeXml));
    m_listWriteXml.insert(
        std::pair<wxString, ifuncWrite>(m_attributeXml.heightRow, &CXmlCodeManager::WriteAttributeXml));

    m_listWriteXml.insert(
        std::pair<wxString, ifuncWrite>(m_attributeTable.webSite, &CXmlCodeManager::WriteAttributeXml));
    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeTable.login, &CXmlCodeManager::WriteAttributeXml));
    m_listWriteXml.insert(
        std::pair<wxString, ifuncWrite>(m_attributeTable.password, &CXmlCodeManager::WriteAttributeXml));

    m_listWriteXml.insert(std::pair<wxString, ifuncWrite>(m_attributeXml.web, &CXmlCodeManager::CreateNodeXml));

    m_attributeUser.push_back(m_attributeTable.webSite);
    m_attributeUser.push_back(m_attributeTable.login);
    m_attributeUser.push_back(m_attributeTable.password);
}

CXmlCodeManager::~CXmlCodeManager()
{
}

void CXmlCodeManager::CreateNodeXml(TAttributeParseXml& attr)
{
    wxString temp = wxString::Format(wxT("%s%d"), attr.name, attr.count++);
    attr.child = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
    attr.parent->AddChild(attr.child);
}

void CXmlCodeManager::WriteAttributeXml(TAttributeParseXml& attr)
{
    attr.child->AddAttribute(attr.name, *(++attr.itr));
}

void CXmlCodeManager::ReadPageXml(wxXmlNode* node)
{
    m_namePage = node->GetAttribute(m_attributeXml.namePage);
}

void CXmlCodeManager::ReadWebXml(wxXmlNode* node)
{
    wxArrayString arrayString;
    for(auto& p : m_attributeUser) {
        arrayString.Add(p);
        arrayString.Add(node->GetAttribute(p, m_attributeXml.notFound));
    }
    SetValue(arrayString);
}
