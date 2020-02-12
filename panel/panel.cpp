#include "panel.h"
#include <wx/stdpaths.h>

CPanel::CPanel(wxWindow* window, wxString namePanel)
    : CBasePanel(window)
{
    m_grid = new wxGrid(this, NewControlId());
    m_grid->CreateGrid(0, 3, wxGrid::wxGridSelectRows);

    // Hide labels rows
    m_grid->SetRowLabelSize(0);

    m_grid->SetColLabelValue(0, m_attribute.webSite);
    m_grid->SetColLabelValue(1, m_attribute.login);
    m_grid->SetColLabelValue(2, m_attribute.password);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_grid, 1, wxEXPAND);
    this->SetSizerAndFit(h_box);
}

CPanel::~CPanel()
{
}

void CPanel::GetValue(wxArrayString& arrayString)
{
    int countRow = m_grid->GetNumberRows();
    int countCol = m_grid->GetNumberCols();

    arrayString.push_back(m_attribute.namePage);
    arrayString.push_back(m_namePage);

    for(int col = 0; col < countCol; col++) {
        arrayString.push_back(m_attribute.widthCol + wxString::Format(wxT("%d"), col));
        arrayString.push_back(wxString::Format(wxT("%d"), m_grid->GetColSize(col)));
    }

    for(int row = 0; row < countRow; row++) {
        arrayString.push_back(m_attribute.heightRow + wxString::Format(wxT("%d"), row));
        arrayString.push_back(wxString::Format(wxT("%d"), m_grid->GetRowHeight(row)));
    }

    for(int row = 0; row < countRow; row++) {
        for(int col = 0; col < countCol; col++) {
            arrayString.push_back(m_grid->GetColLabelValue(col));
            arrayString.push_back(m_grid->GetCellValue(row, col));
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

void CPanel::GetSizeAllColumn(wxArrayInt& ArraySizeCol)
{
    int countCol = m_grid->GetNumberCols();

    m_grid->AutoSize();

    for(int col = 0; col < countCol; col++)
        ArraySizeCol.push_back(m_grid->GetColSize(col));
}

void CPanel::SetSizeAllColumn(const wxArrayInt& ArraySizeCol)
{
    int size = ArraySizeCol.size();
    for(int i = 0; i < size; i++)
        m_grid->SetColSize(i, ArraySizeCol[i]);

    int width = 0;
    int height = 0;

    int countRow = m_grid->GetNumberRows();
    int countCol = m_grid->GetNumberCols();

    for(int col = 0; col < countCol; col++)
        height += m_grid->GetColSize(col);

    for(int row = 0; row < countRow; row++)
        width += m_grid->GetRowSize(row);

    this->SetMinSize(wxSize(height, width));
}

void CPanel::AddNewItem()
{
    m_grid->AppendRows();
}

void CPanel::DeleteItem()
{
    if(m_grid->GetNumberRows() != 0) {
        wxArrayInt arrayNumberRows = m_grid->GetSelectedRows();
        if(arrayNumberRows.empty() == false) {
            wxMessageDialog dlg(this, wxT("Delete item table?"), wxT("Delete item table"), wxOK | wxCANCEL);
            if(dlg.ShowModal() == wxID_OK)
                for(auto& p : arrayNumberRows)
                    m_grid->DeleteRows(p);
        } else
            wxMessageBox(wxT("Selected item from table for delete"));
    } else
        wxMessageBox(wxT("No item for delete"));
}