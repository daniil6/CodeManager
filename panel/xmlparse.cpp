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

template <typename R, typename... P> R CXmlParse::methods(R (*func)(P...), P... params)
{
    if(func != nullptr)
        return (*func)(params...);
}

wxXmlNode* CXmlParse::SaveXmlFileFromList(int page)
{
    int count_web = 0;
    wxArrayString arrayString;
    wxXmlNode* parent = nullptr;
    wxXmlNode* node = nullptr;

    GetValue(arrayString);
    parent = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxString::Format(wxT("page%d"), page));
    node = parent;

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_string = *itr;

        for(auto& p : m_listWriteXml) {
            if(node != nullptr && t_string == p.first) {
                // methods(p.second, parent, node, p.first, itr, count_web);
                TAttributeParseXml attr{ parent, node, p.first, itr, count_web };
                (this->*p.second)(attr);
            }
        }
    }

    return parent;
}
