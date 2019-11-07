#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "panel.h"
#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    wxXmlDocument m_doc;

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
