#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "wx/wx.h"

class CBasePanel : public wxPanel
{
protected:
    wxString m_namePage;

public:
    CBasePanel(wxWindow* window, wxString namePage);
    ~CBasePanel();
};

#endif // CBASEPANEL_H
