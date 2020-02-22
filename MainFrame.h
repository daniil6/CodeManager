#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "panel/panel.h"
#include <wx/listbook.h>
#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    wxListbook* m_choicebook;

    template <typename TReturn, typename TClass, typename... TParam>
    TReturn GetClassMethod(int numPage, TReturn (TClass::*func)(TParam...), TParam... param);

    void ResizePageInListbook();
    void CreateMenuBar();
    void LoadXml();
    void OnSaveXml(wxCommandEvent& event);
    void OnAddNewItem(wxCommandEvent& event);
    void OnDeleteItem(wxCommandEvent& event);
    void OnAddPage(wxCommandEvent& event);
    void OnDeletePage(wxCommandEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
