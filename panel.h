#ifndef CPANEL_H
#define CPANEL_H

#include "wx/wx.h"
#include <wx/listctrl.h>
#include <wx/xml/xml.h>

#define NAMEFILEXML wxT("KeyByAllTheDoor.xml")

struct TAttributeXml {
    wxString webSite = wxT("WebSite");
    wxString login = wxT("Login");
    wxString password = wxT("Password");
};

class CPanel : public wxPanel
{
private:
    TAttributeXml attribute;

    wxString m_namePanel;
    wxXmlDocument m_doc;
    wxListCtrl* m_listCtrl;

    void SetValue(const wxArrayString& arrayString);
    wxArrayString GetValue();

public:
    CPanel(wxWindow* window, wxString namePanel, wxXmlDocument& doc);
    ~CPanel();

    bool SaveXmlFileFromList(wxXmlNode* node);
    void LoadXmlFileInList(wxXmlNode* node);
};

#endif // CPANEL_H
