#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>

using namespace std;
class apiget
{
    public:
        //get apikey etc
        apiget(int);
        virtual ~apiget();
        //getter and setter for court number
        int GetCourtNo() { return CourtNo; }
        void SetCourtNo(int val) { CourtNo = val; }
        //getter and setter for basic URL
        string GetbasicURL() { return basicURL; }
        void SetbasicURL(string val) { basicURL = val; }
        //getter and setter for API key
        string Getapikey() { return apikey; }
        void Setapikey(string val) { apikey = val; }


        //this function gets all the things from the API, gets API information, sets everything up and performs HTTP get
        void getAPIinformation();
    protected:
    private:
        int CourtNo;
        string basicURL;
        string apikey;
};

