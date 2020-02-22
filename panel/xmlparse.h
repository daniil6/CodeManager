#ifndef CXmlParse_H
#define CXmlParse_H

#include "xmlcodemanager.h"

class CXmlParse : public CXmlCodeManager
{
private:
    virtual void SetValue(const wxArrayString& arrayString) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

public:
    CXmlParse(wxWindow* window, wxString namePage);
    ~CXmlParse();

    void LoadXmlFileInList(wxXmlNode* node);
    bool SaveXmlFileFromList(wxXmlNode* mail);
};

#endif // CXmlParse_H