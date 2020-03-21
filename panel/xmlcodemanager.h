#ifndef CXMLCODEMANAGER_H
#define CXMLCODEMANAGER_H

#include "basepanel.h"

struct TAttributeParseXml {
    wxXmlNode* parent;
    wxXmlNode* child;
    int count;
};

class CXmlCodeManager : public CBasePanel, TXmlParse<CXmlCodeManager, TAttributeParseXml>
{
private:
    void ReadWebXml(wxXmlNode* node);
    void ReadPageXml(wxXmlNode* node);

    void WriteAttributeXml(TAttributeParseXml& attribute, ItrType itr);
    void CreateNodeXml(TAttributeParseXml& attribute, ItrType itr);

    virtual void SetValue(const wxArrayString& arrayString, int countAttribute) = 0;
    virtual void GetValue(wxArrayString& arrayString) = 0;

public:
    CXmlCodeManager(wxWindow* window, wxString namePage);
    ~CXmlCodeManager();

    wxXmlNode* Save(int page);
    void Load(wxXmlNode* node);
};

#endif // CXMLCODEMANAGER_H