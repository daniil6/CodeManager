#include "basepanel.h"

CBasePanel::CBasePanel(wxWindow* window, wxString namePage)
    : wxPanel(window, NewControlId())
{
    m_namePage = namePage;

    m_listParamsXml.insert(std::pair<int, wxString>(WEB, wxT("web")));
    m_listParamsXml.insert(std::pair<int, wxString>(PAGE, wxT("page")));
    m_listParamsXml.insert(std::pair<int, wxString>(NAMEPAGE, wxT("NamePage")));
    m_listParamsXml.insert(std::pair<int, wxString>(WIDTHCOL, wxT("WidthCol")));
    m_listParamsXml.insert(std::pair<int, wxString>(HEIGHTROW, wxT("HeightRow")));
    m_listParamsXml.insert(std::pair<int, wxString>(NOT_FOUND, wxT("NOT_FOUND")));
    m_listParamsXml.insert(std::pair<int, wxString>(NEXT, wxT("Next")));
}

CBasePanel::~CBasePanel()
{
}