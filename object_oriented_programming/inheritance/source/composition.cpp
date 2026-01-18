/*
🧩 Problem Statement: Document Export System (C++)
Background

You are building a Document Export System for a desktop application (like a report generator or IDE).

Users can:
Create documents
Apply different export formats
Apply different compression strategies
Apply different encryption strategies
The system must be extensible without modifying existing code.


-------------------------------------------------------------------------------------------------------------------------------

You must follow these rules:

❌ Do NOT use inheritance to model:

Document → PdfDocument
Document → EncryptedDocument
Document → CompressedDocument



Thinking:
Document has a: create, delete, export, compression, encryption  --> composition
export is a: PDF, HTML, markdown --> Interface and sutype
encryption is a: AES, RSA, No encryption --> Interface and sutype
compression is a: .zip, .tar, no compression --> Interface and sutype

Next:
Write UML Diagrams


*/


#include <iostream>
#include <unistd.h>
#include <string>




//Export interface
class IExporter
{
    public:
    virtual ~IExporter() = default;
    virtual bool Export() = 0;

};

class PDFTypeExport : public IExporter
{
    public:
    bool Export() override
    {
        std::cout<<"Exporting via PDF!!!"<<'\n';
    }
};

class HTMLTypeExport : public IExporter
{
    public:
    bool Export() override
    {
        std::cout<<"Exporting via HTML!!!"<<'\n';
    }

};


//Compression Interface
class ICompressor
{
    public:
    virtual ~ICompressor() = default;
    virtual bool Compress() = 0;

};



class ZIPType : public ICompressor
{
    public:
    bool Compress() override
    {
        std::cout<<"ZIPPing it!!!!"<<'\n';
    }
};

class TARType : public ICompressor
{
    public:
    bool Compress() override
    {
        std::cout<<"Taring it!!!!"<<'\n';
    }
};


//encryption Interface

class IEncryptor
{
    public:
    virtual ~IEncryptor() = default;
    virtual bool Encrypt() = 0;
};

class AESType : public IEncryptor
{
    public:
    bool Encrypt() override
    {
        std::cout<<"Encrypting via AES!!!"<<'\n';
    }

};

class RSAType : public IEncryptor
{
    public:
    bool Encrypt() override
    {
        std::cout<<"Encrypting via RSA!!!"<<'\n';
    }

};


class Document
{
    public:
    std::string doc_name;
    ~Document() = default; //delete
    Document(std::string doc_name) //create
    {
        this->doc_name = doc_name;
        std::cout<<"Document "<<doc_name<<" is created!"<<'\n';
    }

    bool export_document(IExporter& exportt)
    {
        if(exportt.Export())
        {
            std::cout<<"Document is exported!"<<'\n';
        }
        
    }

    bool compress_document(ICompressor& compression)
    {
        if(compression.Compress())
        {
            std::cout<<"Document is Compressed!"<<'\n';
        }
        
    }

    bool encrypt_document(IEncryptor& encrypt)
    {
        if(encrypt.Encrypt())
        std::cout<<"Document is Encrypted!"<<'\n';
    }

};

int main()
{
    Document hello("MANJESH");
    Document* sprint_Budget =  new Document("Sprint_budgeting_01");
    IExporter* pdf = new PDFTypeExport();
    ICompressor* zip = new ZIPType();
    IEncryptor* aes = new AESType();
    sprint_Budget->encrypt_document(*aes);
    sprint_Budget->compress_document(*zip);
    sprint_Budget->export_document(*pdf);
    delete sprint_Budget;
    return 0;
}