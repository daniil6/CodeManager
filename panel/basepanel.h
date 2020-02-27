#ifndef CBASEPANEL_H
#define CBASEPANEL_H

#include "wx/wx.h"

class CBasePanel : public wxPanel
{
protected:
    wxString m_namePage;

public:
    enum ProgrammResult { Success = 0, Error };

    CBasePanel(wxWindow* window, wxString namePage);
    ~CBasePanel();
};

#endif // CBASEPANEL_H
