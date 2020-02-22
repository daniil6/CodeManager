#ifndef CXMLCODEMANAGER_H
#define CXMLCODEMANAGER_H

#include <map>
#include <wx/xml/xml.h>

#include "basepanel.h"

struct TAttributeXml {
    wxString web = wxT("web");
    wxString page = wxT("page");
    wxString namePage = wxT("NamePage");
    wxString widthCol = wxT("WidthCol");
    wxString heightRow = wxT("HeightRow");
    wxString notFound = wxT("NOT_FOUND");
    wxString next = wxT("Next");
};

struct TAttributeParseXml {
    wxXmlNode* parent;
    wxXmlNode*& child;
    wxString attributeName;
    wxString* itrAttributeValue;
    int& count;
};

struct TAttributeTable {
    wxString webSite = wxT("WebSite");
    wxString login = wxT("Login");
    wxString password = wxT("Password");
};

class CXmlCodeManager : public CBasePanel
{
private:
    std::vector<wxString> m_attributeUser;

    typedef void (CXmlCodeManager::*ifuncRead)(wxXmlNode*);
    typedef void (CXmlCodeManager::*ifuncWrite)(TAttributeParseXml&);

    void ReadWebXml(wxXmlNode* node);
    void ReadPageXml(wxXmlNode* node);

    void WriteAttributeXml(TAttributeParseXml& attribute);
    void CreateNodeXml(TAttributeParseXml& attribute);

    virtual void SetValue(const wxArrayString& arrayString) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

protected:
    TAttributeXml m_attributeXml;
    TAttributeTable m_attributeTable;

    std::map<wxString, ifuncRead> m_listReadXml;
    std::map<wxString, ifuncWrite> m_listWriteXml;

public:
    CXmlCodeManager(wxWindow* window, wxString namePage);
    ~CXmlCodeManager();
};

#endif // CXMLCODEMANAGER_H