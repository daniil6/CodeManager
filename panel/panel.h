#ifndef CPANEL_H
#define CPANEL_H

#include "base_panel.h"
#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/xml/xml.h>

#define NAMEFILEXML wxT("KeyByAllTheDoor.xml")
#define ROOTXML wxT("root")

class CPanel : public CBasePanel
{
private:
    wxString m_namePanel;
    wxGrid* m_grid;
    wxListCtrl* m_listCtrl;

    virtual void SetValue(const wxArrayString& arrayString) final;
    virtual void GetValue(wxArrayString& arrayString) final;

public:
    CPanel(wxWindow* window, wxString namePanel);
    ~CPanel();

    void AddNewItem();
    void DeleteItem();
};

#endif // CPANEL_H
