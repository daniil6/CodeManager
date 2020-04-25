#include "settingspage.h"

CSettingsPage::CSettingsPage(wxWindow* parent)
    : wxDialog(parent,
          NewControlId(),
          wxT("Settings page"),
          wxDefaultPosition,
          wxDefaultSize,
          wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE)
{
    this->SetBackgroundColour(*wxWHITE);

    wxTextCtrl* txtNamePage = new wxTextCtrl(this, NewControlId(), wxT(""));

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);

    wxStaticBoxSizer* st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Name page"));
    st_box->Add(txtNamePage, 1, wxEXPAND);

    main_box->Add(st_box, 0, wxEXPAND);
    main_box->Add(new ScrolledWidgetsPane(this), 1, wxEXPAND);

    SetSizerAndFit(main_box);
}

CSettingsPage::~CSettingsPage()
{
}