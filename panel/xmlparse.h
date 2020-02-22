#ifndef CXmlParse_H
#define CXmlParse_H

#include "xmlcodemanager.h"

class CXmlParse : public CXmlCodeManager
{
private:
    virtual void SetValue(const wxArrayString& arrayString) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

    template <typename R, typename... P> R methods(R (*func)(P...), P... params);

public:
    CXmlParse(wxWindow* window, wxString namePage);
    ~CXmlParse();

    void LoadXmlFileInList(wxXmlNode* node);
    wxXmlNode* SaveXmlFileFromList(int page);
};

#endif // CXmlParse_H