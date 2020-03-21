#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "xmlparse_template.h"
#include "wx/wx.h"

typedef std::map<int, wxString> ListParamsXml;

class CBasePanel : public wxPanel
{
protected:
    enum ParamsXml { WEB = 0, PAGE, NAMEPAGE, WIDTHCOL, HEIGHTROW, NOT_FOUND, NEXT, END_PARAMS };
    ListParamsXml m_listParamsXml;
    wxString m_namePage;

public:
    CBasePanel(wxWindow* window, wxString namePage);
    ~CBasePanel();
};

#endif // CBASEPANEL_H
