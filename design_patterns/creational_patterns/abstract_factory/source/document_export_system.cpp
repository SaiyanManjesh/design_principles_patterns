/*

You are building a software tool used in companies that can export reports.
Users can generate a report and export it in different formats.

Example formats
PDF
Excel
CSV
JSON

Requirements
1. User selects format
Export as:
[ PDF ]
[ Excel ]
[ CSV ]
[ JSON ]

2. System workflow
When user clicks Export:
1. Create the correct exporter
2. Convert report data
3. Save the file

3. Future changes
Later the company might add:
XML export
HTML export
Google Sheets export
Database export
So the system must be easy to extend.


//FUTURE PROOFING
4. Each format has its own logic
PDF export
uses a PDF rendering library
supports fonts and layout
compresses images
Excel export
uses spreadsheet library
supports sheets and formulas
CSV export
simple text format
comma separated values
JSON export
structured nested data
Each format is implemented differently.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Design thinking
1. Export formats (INTERFACE)
PDF
Excel
CSV
Excel
In future it can be more also


2. User clicks on type of export button and it automatically exports (FACTORY Where when user clicks exporting should happen)


Flow:
user clicks on the type of option
EXPORT TYPE instance cretead
then user clicks save
then the file will saved

*/


#include <iostream>
#include <stdio.h>
#include <string>



class Export
{
    public:
    virtual ~Export() = default;
    virtual void _export() = 0;
};


class PDFExport : public Export
{
    std::string message;
    public:
    PDFExport(std::string message)
    {
        this->message = message;
    }
    void _export() override
    {
        // Future will add the actual exporting methods
        std::cout<<"Exporting via PDF! and the message is "<<this->message<<"\n";
    }
};

class ExcelExport : public Export
{
    std::string message;
    public:
    ExcelExport(std::string message)
    {
        this->message = message;
    }
    void _export() override
    {
        // Future will add the actual exporting methods
        std::cout<<"Exporting via Excel! and the message is "<<this->message<<"\n";
    }
};

class JSONExport : public Export
{
    std::string message;
    public:
    JSONExport(std::string message)
    {
        this->message = message;
    }
    void _export() override
    {
        // Future will add the actual exporting methods
        std::cout<<"Exporting via JSON! and the message is "<<this->message<<"\n";
    }
};

enum class ExportType
{
    PDF,
    Excel,
    JSON
};


class ExportFactory
{
    Export * exporting_type;
    
    public:

    static Export *create(ExportType type, std::string message)
    {
        
        if(type == ExportType::Excel)
        {
            return new ExcelExport(message);
        }

        else if (type == ExportType::JSON)
        {
            return new JSONExport(message);
        }
        else if( type == ExportType::PDF)
        {
            return new PDFExport(message);
        }

        else
        {
            std::cout<<"ehnlo This type is not supported in this software. Please choose propely again!"<<"\n";
            return NULL;
        }

    }
};



int main()
{

    while(1)
    {
        int user_input = 0;
        ExportFactory *factory  =  new ExportFactory();
        Export *exporter = NULL;
        std::cout<<"select the EXPORT Type"<<"\n";
        std::cout<< "1 . PDF"<<"\n";
        std::cout<< "2 . Excel"<<"\n";
        std::cout<< "3 . JSON"<<"\n";
        std::cin>>user_input;

        switch(user_input)
        {
            case 1:
            exporter = ExportFactory::create(ExportType::PDF, "VIRAT KHAN");
            break;

            case 2:
            exporter = ExportFactory::create(ExportType::Excel, "MANJESH PATIL");
            break;

            case 3:
            exporter = ExportFactory::create(ExportType::JSON, "VADA PAV");
            break;

            default:
            std::cout<<"This type is not supported in this software. Please choose propely again!"<<"\n";
            break;
            
        }
        if(exporter != NULL)
        {
            exporter->_export();
        }
       
        delete factory;
        delete exporter;
    }

    return 0;
}