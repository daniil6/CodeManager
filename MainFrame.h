#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <wx/listbook.h>
#include <wx/wx.h>
#include "panel/panel.h"

class CMainFrame : public wxFrame
{
private:
    wxXmlDocument m_xmlDocument;
    wxListbook* m_choicebook;

    void CreateMenuBar();
    void OnSaveXml(wxCommandEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
