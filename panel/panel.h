#ifndef CPANEL_H
#define CPANEL_H

#include "xmlparse.h"
#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/xml/xml.h>

#define NAMEFILEXML wxT("KeyByAllTheDoor.xml")
#define ROOTXML wxT("root")

class CPanel : public CXmlParse
{
private:
    wxGrid* m_grid;
    wxListCtrl* m_listCtrl;

    virtual void SetValue(const wxArrayString& arrayString) final;
    virtual void GetValue(wxArrayString& arrayString) final;

public:
    CPanel(wxWindow* window, wxString namePanel);
    ~CPanel();

    bool AddNewItem();
    void DeleteItem();
    void GetSizeAllColumn(wxArrayInt& ArraySizeCol);
    void SetSizeAllColumn(const wxArrayInt& ArraySizeCol);
};

#endif // CPANEL_H
