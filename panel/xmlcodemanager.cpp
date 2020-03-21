#include "xmlcodemanager.h"

CXmlCodeManager::CXmlCodeManager(wxWindow* window, wxString namePage)
    : CBasePanel(window, namePage)
    , TXmlParse(this)
{
    TXmlParse::SetRead(m_listParamsXml[PAGE], this->ReadPageXml);
    TXmlParse::SetRead(m_listParamsXml[WEB], this->ReadWebXml);

    TXmlParse::SetWrite(m_listParamsXml[WEB], this->CreateNodeXml);
    TXmlParse::SetWrite(m_listParamsXml[NAMEPAGE], this->WriteAttributeXml);
    TXmlParse::SetWrite(m_listParamsXml[WIDTHCOL], this->WriteAttributeXml);
    TXmlParse::SetWrite(m_listParamsXml[HEIGHTROW], this->WriteAttributeXml);
}

CXmlCodeManager::~CXmlCodeManager()
{
}

void CXmlCodeManager::CreateNodeXml(TAttributeParseXml& attr, ItrType itr)
{
    wxString temp = wxString::Format(wxT("%s%d"), *itr, attr.count++);
    attr.child = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, temp);
    attr.parent->AddChild(attr.child);
}

void CXmlCodeManager::WriteAttributeXml(TAttributeParseXml& attr, ItrType itr)
{
    if(attr.child != nullptr) {
        wxString temp = *itr;
        ++itr;
        attr.child->AddAttribute(temp, *itr);
    }
}

void CXmlCodeManager::ReadPageXml(wxXmlNode* node)
{
    m_namePage = node->GetAttribute(m_listParamsXml[NAMEPAGE]);
}

void CXmlCodeManager::ReadWebXml(wxXmlNode* node)
{
    int countAttribute = 0;
    wxArrayString arrayString;
    wxXmlAttribute* xmlAttribute = node->GetAttributes();
    while(xmlAttribute != nullptr) {
        countAttribute++;
        wxString nameAttribute = xmlAttribute->GetName();
        TXmlParse::SetWrite(nameAttribute, this->WriteAttributeXml);
        arrayString.Add(nameAttribute);
        arrayString.Add(xmlAttribute->GetValue());
        xmlAttribute = xmlAttribute->GetNext();
    }

    SetValue(arrayString, countAttribute);
}

wxXmlNode* CXmlCodeManager::Save(int page)
{
    wxArrayString arrayString;

    GetValue(arrayString);

    TAttributeParseXml attr;
    attr.parent = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxString::Format(wxT("page%d"), page));
    attr.child = attr.parent;
    attr.count = 0;

    TXmlParse::Write(&attr, arrayString);

    return attr.parent;
}

void CXmlCodeManager::Load(wxXmlNode* node)
{
    TXmlParse::Read(node);
}