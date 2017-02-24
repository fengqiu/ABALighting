#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>

using namespace std;
class apiget
{
    public:
        apiget(int);
        virtual ~apiget();
        int GetCourtNo() { return CourtNo; }
        void SetCourtNo(int val) { CourtNo = val; }
        string GetbasicURL() { return basicURL; }
        void SetbasicURL(string val) { basicURL = val; }
        string Getapikey() { return apikey; }
        void Setapikey(string val) { apikey = val; }
        void getAPIinformation();
    protected:
    private:
        int CourtNo;
        string basicURL;
        string apikey;
};

