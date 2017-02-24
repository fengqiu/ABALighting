#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class ReadConfig
{
    public:
        ReadConfig();
        ReadConfig(string);
        string GetFileName() { return FileName; }
        void SetFileName(string val) { FileName = val; }
        vector<string> GetContents() { return Contents; }
        void SetContents(vector<string> val) { Contents = val; }
        vector<int> GetCourtNo() { return CourtNo; }
        void SetCourtNo(vector<int> val) { CourtNo = val; }
        vector<int> GetTiggerPin() { return TriggerPin; }
        void SetTriggerPin(vector<int> val) { TriggerPin = val; }
    protected:
    private:
        string FileName;
        vector<string> Contents;
        vector<int> CourtNo;
        vector<int> TriggerPin;
};
