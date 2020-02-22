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

bool CXmlParse::SaveXmlFileFromList(wxXmlNode* mail)
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
