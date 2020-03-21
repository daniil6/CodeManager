#ifndef CPANEL_H
#define CPANEL_H

#include "xmlcodemanager.h"
#include <wx/grid.h>

#define NAMEFILEXML wxT("KeyByAllTheDoor.xml")

class CPanel : public CXmlCodeManager
{
private:
    wxGrid* m_grid;

    void GetSizeCell(wxArrayString& array, int count, int number, int (wxGrid::*ifunc)(int) const);

    virtual void SetValue(const wxArrayString& arrayString, int countAttribute) final;
    virtual void GetValue(wxArrayString& arrayString) final;

public:
    CPanel(wxWindow* window, wxString namePanel);
    ~CPanel();

    bool AddNewItem();
    bool DeleteItem();
    bool GetSizeAllColumn(wxArrayInt& ArraySizeCol);
    bool SetSizeAllColumn(const wxArrayInt& ArraySizeCol);
};

#endif // CPANEL_H
