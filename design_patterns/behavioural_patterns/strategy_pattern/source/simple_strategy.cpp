#include <iostream>
#include <string>

class IHash
{
    public:
    virtual ~IHash() = default;

    virtual int compute_hash(std::string buffer, int size)  = 0;

};


class SHA256_Hash : public IHash
{
    public:
    int compute_hash(std::string buffer, int size) override
    {
        std::cout<<"Compute Hash has been called from SHA256!!"<<"\n";
        return 0;
    }
};


class MD5_Hash : public IHash
{
    public:
    int compute_hash(std::string buffer, int size) override
    {
        std::cout<<"Compute Hash has been called from MD5!!"<<"\n";
        return 0;
    }
};


class AES_Hash : public IHash
{
    public:
    int compute_hash(std::string buffer, int size) override
    {
        std::cout<<"Compute Hash has been called from AES!!"<<"\n";
        return 0;
    }
};



class Cryptograph
{
    IHash *select_hash;
    public:

    // Important!!! ---- Allow Strategy Switching at run time or else One hash at run time == bad design
    void set_hash(IHash *set_hash)
    {
        this->select_hash = set_hash;
    }

    void compute_hash(std::string buffer, int size)
    {
        select_hash->compute_hash(buffer, size);
    }
};


int main()
{

    Cryptograph *crypt = new Cryptograph();
    crypt->set_hash(new AES_Hash());

    crypt->compute_hash("HELLO MANJESH", 10);

    crypt->set_hash(new MD5_Hash());
    crypt->compute_hash("PATIL", 10);


    return 0;
}