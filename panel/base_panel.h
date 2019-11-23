#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "wx/wx.h"
#include <wx/xml/xml.h>

struct TAttributeXml {
    wxString webSite = wxT("WebSite");
    wxString login = wxT("Login");
    wxString password = wxT("Password");
};

class CBasePanel : public wxPanel
{
private:
protected:
    TAttributeXml attribute;
    virtual void SetValue(const wxArrayString& arrayString) = 0;

public:
    CBasePanel(wxWindow* window);
    ~CBasePanel();

    void LoadXmlFileInList(wxXmlNode* node);
};

#endif // CBASEPANEL_H
