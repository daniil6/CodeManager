#ifndef CPANEL_H
#define CPANEL_H

#include <wx/listctrl.h>
#include <wx/xml/xml.h>
#include "base_panel.h"

#define NAMEFILEXML wxT("KeyByAllTheDoor.xml")
#define ROOTXML wxT("root")

class CPanel : public CBasePanel
{
private:


    wxString m_namePanel;
    wxXmlDocument m_doc;
    wxListCtrl* m_listCtrl;

    virtual void SetValue(const wxArrayString& arrayString) final;
    wxArrayString GetValue();

public:
    CPanel(wxWindow* window, wxString namePanel, wxXmlDocument& doc);
    ~CPanel();

    bool SaveXmlFileFromList(wxXmlNode* node);
    void LoadXmlFileInList(wxXmlNode* node);
};

#endif // CPANEL_H
