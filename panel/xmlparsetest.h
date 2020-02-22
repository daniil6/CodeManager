#ifndef CXMLPARSETEST_H
#define CXMLPARSETEST_H

#include <wx/xml/xml.h>

class CXmlParseTest
{
public:
    CXmlParseTest();
    ~CXmlParseTest();

    static wxXmlDocument InitXmlFile()
    {
        wxXmlDocument xmlDoc;
        xmlDoc.SetRoot(new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("root")));
        return xmlDoc;
    }

    static void CloseXmlFile(wxXmlNode* root, wxString nameFile)
    {
        wxXmlDocument xmlDoc;
        xmlDoc.SetRoot(root);
        xmlDoc.Save(nameFile);
    }
};

#endif // CXMLPARSETEST_H