#include "xmlparse.h"

CXmlParse::CXmlParse(wxWindow* window, wxString namePage)
    : CXmlCodeManager(window, namePage)
{
}

CXmlParse::~CXmlParse()
{
}

void CXmlParse::LoadXmlFileInList(wxXmlNode* node)
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

wxXmlNode* CXmlParse::SaveXmlFileFromList(int page)
{
    wxArrayString arrayString;

    GetValue(arrayString);

    TAttributeParseXml attr;
    attr.parent = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxString::Format(wxT("page%d"), page));
    attr.child = attr.parent;
    attr.count = 0;

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        for(auto& p : m_listWriteXml) {
            if(attr.child != nullptr && *itr == p.first) {
                attr.name = p.first;
                attr.itr = itr;
                (this->*p.second)(attr);
            }
        }
    }

    return attr.parent;
}
