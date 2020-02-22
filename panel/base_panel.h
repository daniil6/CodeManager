#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "wx/wx.h"
#include <map>
#include <wx/xml/xml.h>

struct TAttributeXml {
    wxString web = wxT("web");
    wxString page = wxT("page");
    wxString namePage = wxT("NamePage");
    wxString widthCol = wxT("WidthCol");
    wxString heightRow = wxT("HeightRow");
    wxString notFound = wxT("NOT_FOUND");
    wxString next = wxT("Next");
};

struct TAttributeTable {
    wxString webSite = wxT("WebSite");
    wxString login = wxT("Login");
    wxString password = wxT("Password");
};

struct TAttributeParseXml {
    wxXmlNode* parent;
    wxXmlNode*& child;
    wxString attributeName;
    wxString* itrAttributeValue;
    int& count;
};

class CBasePanel : public wxPanel
{
private:
    typedef void (CBasePanel::*ifuncRead)(wxXmlNode*);
    typedef void (CBasePanel::*ifuncWrite)(TAttributeParseXml&);

    std::map<wxString, ifuncRead> m_listReadXml;
    std::map<wxString, ifuncWrite> m_listWriteXml;

    void ReadWebXml(wxXmlNode* node);
    void ReadPageXml(wxXmlNode* node);

    void WriteAttributeXml(TAttributeParseXml& attribute);
    void CreateNodeXml(TAttributeParseXml& attribute);

protected:
    wxString m_namePage;
    TAttributeXml m_attributeXml;
    TAttributeTable m_attributeTable;
    std::vector<wxString> m_attributeUser;
    virtual void SetValue(const wxArrayString& arrayString) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

public:
    CBasePanel(wxWindow* window, wxString namePage);
    ~CBasePanel();

    void LoadXmlFileInList(wxXmlNode* node);
    bool SaveXmlFileFromList(wxXmlNode* mail);
};

#endif // CBASEPANEL_H