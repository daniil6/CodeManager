#include "panel.h"
#include <wx/stdpaths.h>

CPanel::CPanel(wxWindow* window, wxString namePanel)
    : CBasePanel(window)
    , m_namePanel(namePanel)
{
    m_grid = new wxGrid(this, NewControlId());
    m_grid->CreateGrid(0, 5);

    // Hide labels rows
    m_grid->SetRowLabelSize(0);

    m_grid->SetColLabelValue(0, m_attribute.webSite);
    m_grid->SetColLabelValue(1, m_attribute.login);
    m_grid->SetColLabelValue(2, m_attribute.password);
    m_grid->SetColLabelValue(3, m_attribute.mail);
    m_grid->SetColLabelValue(4, m_attribute.web);

    // m_listCtrl = new wxListCtrl(this, NewControlId(), wxDefaultPosition, wxDefaultSize, wxLC_REPORT |
    // wxLC_EDIT_LABELS);  m_listCtrl->InsertColumn(0, attribute.webSite);  m_listCtrl->InsertColumn(1,
    // attribute.login); m_listCtrl->InsertColumn(2, attribute.password);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_grid, 1, wxEXPAND);
    this->SetSizerAndFit(h_box);
}

CPanel::~CPanel()
{
}

void CPanel::GetValue(wxArrayString& arrayString)
{
    long itemIndex = -1;
    while((itemIndex = m_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND) {
        wxListItem item;
        item.SetId(itemIndex);
        item.SetMask(wxLIST_MASK_TEXT);

        for(int col = 0; col < m_listCtrl->GetColumnCount(); col++) {
            item.SetColumn(col);
            m_listCtrl->GetItem(item);
            wxString itemColumm = item.GetText();
            m_listCtrl->GetColumn(col, item);
            wxString labelColumm = item.GetText();

            arrayString.push_back(labelColumm);
            arrayString.push_back(itemColumm);
        }
    }
}

void CPanel::SetValue(const wxArrayString& arrayString)
{
    m_grid->AppendRows();

    int countRow = m_grid->GetNumberRows() - 1;
    int countCol = m_grid->GetNumberCols();

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        wxString t_str = *itr;
        for(int i = 0; i < countCol; i++)
            if(t_str == m_grid->GetColLabelValue(i))
                m_grid->SetCellValue(countRow, i, *(++itr));
    }
}

void CPanel::AddNewItem()
{
    long itemIndex = m_listCtrl->InsertItem(m_listCtrl->GetItemCount(), wxT("####"));
    for(int i = 0; i < m_listCtrl->GetColumnCount(); i++)
        m_listCtrl->SetItem(itemIndex, i, wxT("####"));
}

void CPanel::DeleteItem()
{
    long itemIndex = -1;
    itemIndex = m_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    m_listCtrl->DeleteItem(itemIndex);
}