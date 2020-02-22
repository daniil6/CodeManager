#include "basepanel.h"

CBasePanel::CBasePanel(wxWindow* window, wxString namePage)
    : wxPanel(window, NewControlId())
{
    m_namePage = namePage;
}

CBasePanel::~CBasePanel()
{
}
