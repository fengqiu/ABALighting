#include "apiget.h"

apiget::apiget(int courtno)
{
    //ctor
    //here we should read a config file to get the URL for
    //read file
    CourtNo=courtno;
    fstream myFile("APIInformation");
    if (myFile.is_open())
    {
        //cycling through my file
        while (myFile.good())
        {
            string line;
            getline(myFile,line);
            stringstream getInformation(line);
            //we only want the second one
            string Value;
            getline(getInformation,Value,':');
            cout<<Value<<endl;
            if(Value.compare("API URL")==0)
            {
                //if it's a url store it into the url
                getline(getInformation,basicURL,';');
                cout<<"Prefix URL = "<<basicURL<<endl;
            }
            else if(Value.compare("API KEY")==0)
            {
                //if it's a apikey store it in it
                getline(getInformation,apikey,';');
                cout<<"API KEY = "<<apikey<<endl;
            }
            getInformation.str("");
        }
    }
    myFile.close();
}
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
//mymethods
void apiget::getAPIinformation()
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *list = NULL;
    apikey=""+apikey;
    string apikeystring="api_key: "+apikey;
    //cout<<apikeystring<<endl;
    list = curl_slist_append(list, apikeystring.c_str());
    curl = curl_easy_init();
    if(curl)
    {
        string courtnumber = to_string(CourtNo);
        string address = basicURL+"court="+courtnumber;
        //cout<<address<<endl;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER ,list);
         /* use a GET to fetch this */
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        string writeData="Court"+to_string(CourtNo)+"Bookings";
        //cout<<writeData<<endl;
        FILE *fp = fopen(writeData.c_str(),"w");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);


        /* Perform the requsest, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

apiget::~apiget()
{
    //dtor
}
