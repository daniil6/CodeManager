#ifndef TXmlParse_H
#define TXmlParse_H

#include <map>
#include <wx/xml/xml.h>

typedef const wxString* ItrType;

template <typename TClass, typename TArgs> class TXmlParse
{
private:
    typedef void (TClass::*ifuncRead)(wxXmlNode*);
    typedef void (TClass::*ifuncWrite)(TArgs&, ItrType itr);

    typedef std::map<wxString, ifuncRead> ListReadXml;
    typedef std::map<wxString, ifuncWrite> ListWriteXml;

    TClass* m_class;

    ListWriteXml m_listWrite;
    ListReadXml m_listRead;

protected:
    void SetWrite(wxString id, ifuncWrite func)
    {
        m_listWrite.insert(std::pair<wxString, ifuncWrite>(id, func));
    }

    void Write(TArgs* args, const wxArrayString& arrayString)
    {
        for(auto itr = arrayString.begin(); itr != arrayString.end(); ++itr)
            for(auto& p : m_listWrite)
                if(m_class != nullptr && *itr == p.first)
                    (m_class->*p.second)(*args, itr);
    }

    void SetRead(wxString id, ifuncRead func)
    {
        m_listRead.insert(std::pair<wxString, ifuncRead>(id, func));
    }

    void Read(wxXmlNode* node)
    {
        while(node != nullptr) {

            for(auto& p : m_listRead)
                if(node->GetName().Find(p.first) != -1)
                    (m_class->*p.second)(node);

            if(node->GetChildren() != nullptr)
                node = node->GetChildren();
            else
                node = node->GetNext();
        }
    }

public:
    TXmlParse(TClass* tClass)
        : m_class(tClass){};
    ~TXmlParse(){};

    static wxXmlNode* Open(wxXmlDocument& xmlDoc, const wxString& nameFile, wxString nameRoot = wxT("root"))
    {
        wxXmlNode* root = nullptr;

        if(xmlDoc.Load(nameFile) == false)
            return nullptr;

        root = xmlDoc.GetRoot();
        if(root->GetName() == nameRoot)
            return root->GetChildren();
        else
            return nullptr;
    }

    static void Close(wxXmlNode* root, wxString nameFile = wxT("output.xml"))
    {
        wxXmlDocument xmlDoc;
        xmlDoc.SetRoot(root);
        xmlDoc.Save(nameFile);
    }
};

#endif // TXmlParse_H