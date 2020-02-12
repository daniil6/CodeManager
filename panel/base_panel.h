#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "wx/wx.h"
#include <wx/xml/xml.h>

struct TAttributeXml {
    wxString web = wxT("web");
    wxString page = wxT("page");
    wxString namePage = wxT("NamePage");
    wxString widthCol = wxT("WidthCol");
    wxString heightRow = wxT("HeightRow");
    wxString notFound = wxT("NOT_FOUND");
};

struct TAttributeTable {
    wxString webSite = wxT("WebSite");
    wxString login = wxT("Login");
    wxString password = wxT("Password");
};

class CBasePanel : public wxPanel
{
private:
protected:
    wxString m_namePage;
    TAttributeXml m_attributeXml;
    TAttributeTable m_attributeTable;
    std::vector<wxString> m_attributeUser;
    virtual void SetValue(const wxArrayString& arrayString) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

public:
    CBasePanel(wxWindow* window);
    ~CBasePanel();

    void LoadXmlFileInList(wxXmlNode* node);
    bool SaveXmlFileFromList(wxXmlNode* mail);
};

#endif // CBASEPANEL_H
