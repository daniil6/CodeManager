#include "panel.h"
#include <wx/stdpaths.h>

CPanel::CPanel(wxWindow* window, wxString namePanel)
    : CXmlCodeManager(window, namePanel)
{
    m_grid = new wxGrid(this, NewControlId());
    m_grid->CreateGrid(0, 0, wxGrid::wxGridSelectRows);

    // Hide labels rows
    m_grid->SetRowLabelSize(0);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_grid, 1, wxEXPAND);
    this->SetSizerAndFit(h_box);
}

CPanel::~CPanel()
{
}

void CPanel::GetSizeCell(wxArrayString& array, int count, int number, int (wxGrid::*ifunc)(int) const)
{
    wxString t_string;
    for(int i = 0; i < count; i++)
        t_string.append(wxString::Format(wxT("%d;"), (m_grid->*ifunc)(i)));

    array.push_back(m_listParamsXml[number]);
    array.push_back(t_string);
}

void CPanel::GetValue(wxArrayString& arrayString)
{
    int countRow = m_grid->GetNumberRows();
    int countCol = m_grid->GetNumberCols();

    arrayString.push_back(m_listParamsXml[NAMEPAGE]);
    arrayString.push_back(m_namePage);

    GetSizeCell(arrayString, countCol, WIDTHCOL, &wxGrid::GetColSize);
    GetSizeCell(arrayString, countRow, HEIGHTROW, &wxGrid::GetRowSize);

    for(int row = 0; row < countRow; row++) {
        arrayString.push_back(m_listParamsXml[WEB]);
        for(int col = 0; col < countCol; col++) {
            arrayString.push_back(m_grid->GetColLabelValue(col));
            arrayString.push_back(m_grid->GetCellValue(row, col));
        }
    }
}

void CPanel::SetValue(const wxArrayString& arrayString, int countAttribute)
{
    m_grid->AppendRows();

    int countRow = m_grid->GetNumberRows() - 1;
    int col = 0;

    while(m_grid->GetNumberCols() < countAttribute)
        m_grid->AppendCols();

    for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr) {
        m_grid->SetColLabelValue(col, *itr);
        m_grid->SetCellValue(countRow, col++, *(++itr));
    }
}

bool CPanel::GetSizeAllColumn(wxArrayInt& ArraySizeCol)
{
    m_grid->AutoSize();

    int countCol = m_grid->GetNumberCols();
    for(int col = 0; col < countCol; col++)
        ArraySizeCol.push_back(m_grid->GetColSize(col));

    return true;
}

bool CPanel::SetSizeAllColumn(const wxArrayInt& ArraySizeCol)
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

    return true;
}

bool CPanel::AddNewItem()
{
    return m_grid->AppendRows();
}

bool CPanel::DeleteItem()
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

    return true;
}