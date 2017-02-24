#ifndef SDFSDF_H
#define SDFSDF_H


class sdfsdf
{
    public:
        sdfsdf();
        virtual ~sdfsdf();
        string Getapikey() { return apikey; }
        void Setapikey(string val) { apikey = val; }
    protected:
    private:
        string apikey;
};

#endif // SDFSDF_H
