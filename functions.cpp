#include "functions.h"
vector<Court> GenerateCourts(ReadConfig Config)
{
    //gets the amount of courts there are
    int CourtCount = Config.GetContents().size();
    //initialisng courts
    vector<Court> AllCourts;
    vector<apiget> CourtAPI;
    vector<int> CourtNumber=Config.GetCourtNo();
    vector<int> Pin=Config.GetTiggerPin();
    for (int i=0;i<CourtCount;i++)
    {
        //create a vector of courts which will be all my courts
        Court SingleCourt(CourtNumber[i],false,Pin[i]);
        cout<<"adding to Courts  "<<to_string(CourtNumber[i])<<"   With GPIO pin: "<<to_string(Pin[i])<<endl;
        AllCourts.push_back(SingleCourt);
        //create vector for all APIs
        apiget SingleAPIget(CourtNumber[i]);
        cout<<"adding to API  "<<to_string(CourtNumber[i])<<endl;
        CourtAPI.push_back(SingleAPIget);
    }
    return AllCourts;
}
vector<apiget> GenerateAPI(ReadConfig Config)
{
    //gets the amount of courts there are
    int CourtCount = Config.GetContents().size();
    //initialisng courts
    vector<apiget> CourtAPI;
    vector<int> CourtNumber=Config.GetCourtNo();
    vector<int> Pin=Config.GetTiggerPin();
    for (int i=0;i<CourtCount;i++)
    {
        //create vector for all APIs
        apiget SingleAPIget(CourtNumber[i]);
        cout<<"adding to API  "<<to_string(CourtNumber[i])<<endl;
        CourtAPI.push_back(SingleAPIget);
        //sync all the apis
        SingleAPIget.getAPIinformation();
    }
    return CourtAPI;
}
