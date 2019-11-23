#include "base_panel.h"

CBasePanel::CBasePanel(wxWindow* window)
    : wxPanel(window, NewControlId())
{
}

CBasePanel::~CBasePanel()
{
}

void CBasePanel::LoadXmlFileInList(wxXmlNode* node)
{
    while(node != nullptr) {
        wxArrayString arrayString;
        arrayString.Add(node->GetName());
        arrayString.Add(node->GetAttribute(attribute.login, wxT("NOT_FOUND")));
        arrayString.Add(node->GetAttribute(attribute.password, wxT("NOT_FOUND")));
        SetValue(arrayString);
        node = node->GetNext();
    }
}