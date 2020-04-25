#ifndef CSETTINGSPAGE_H
#define CSETTINGSPAGE_H

#include <map>
#include <wx/wx.h>

class ScrolledWidgetsPane : public wxScrolledWindow
{
private:
    typedef std::pair<wxSizer*, wxTextCtrl*> ItemLabel;
    typedef std::map<int, ItemLabel> ListLabel;
    ListLabel m_list;

    wxBoxSizer* m_mainBox;
    wxTextCtrl* m_previousTxt;

    std::vector<wxBoxSizer*> m_box;

public:
    ScrolledWidgetsPane(wxWindow* parent)
        : wxScrolledWindow(parent, NewControlId())
    {
        const char* label[] = { "WebSite", "Login", "Password", "" };
        m_previousTxt = new wxTextCtrl(this, NewControlId(), label[0], wxPoint(-1, -1), wxSize(-1, -1));

        m_mainBox = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
        h_box->Add(m_previousTxt, 1);
        m_mainBox->Add(h_box, 0, wxEXPAND);

        m_box.push_back(h_box);

        for(int i = 1; i < 4; i++)
            AddLabel(label[i]);

        // this->SetSizer(m_mainBox);
        this->SetSizerAndFit(m_mainBox);
        this->SetScrollRate(5, 5);
    }

    void AddLabel(const char* label)
    {
        wxTextCtrl* txt = new wxTextCtrl(this, NewControlId(), label, wxPoint(-1, -1), wxSize(-1, -1));
        wxStaticBitmap* btm = new wxStaticBitmap(this, NewControlId(), wxICON(cross), wxPoint(-1, -1), wxSize(10, 10));

        wxSizer* prev_box = m_mainBox->GetItem(m_mainBox->GetItemCount() - 1)->GetSizer();
        prev_box->Prepend(btm, 0, wxALIGN_CENTER_VERTICAL);

        wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
        h_box->Add(txt, 1);
        m_mainBox->Add(h_box, 0, wxEXPAND);
        m_box.push_back(h_box);

        btm->Bind(wxEVT_LEFT_DOWN, &ScrolledWidgetsPane::OnDeleteItem, this);

        m_list.insert(std::make_pair(btm->GetId(), std::make_pair(prev_box, m_previousTxt)));
        m_previousTxt = txt;
    }

    void OnDeleteItem(wxMouseEvent& event)
    {
        auto t = m_list[event.GetId()];

        m_mainBox->Detach(t.first);

        delete this->FindWindow(event.GetId());
        delete t.second;

        m_list.erase(event.GetId());

        Layout();
        this->Fit();
    }
};

class CSettingsPage : public wxDialog
{
private:
    std::vector<wxTextCtrl*> m_list;

    void OnDeleteItem(wxMouseEvent& event);

public:
    wxString GetValue()
    {
        return wxT("");
    }

    CSettingsPage(wxWindow* parent);
    ~CSettingsPage();
};

#endif // CSETTINGSPAGE_H