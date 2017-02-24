#include "ReadConfig.h"
ReadConfig::ReadConfig()
{
}
ReadConfig::ReadConfig(string filename)
{
    //ctor
    //creating a ifstream
    fstream myfile(filename.c_str());
    FileName=filename;
    Contents.clear();
    //open my file
    if (myfile.is_open())
    {
        //assigning
        string line;
        while(getline(myfile,line))
        {
            Contents.push_back(line);
        }
    }
    //if we could not open file
    else
    {
        cout<<"could not open file"<<endl;
    }
    myfile.close();
    //lets get another open a whole range of files now
    for (unsigned int i=0;i<Contents.size();i++)
    {
        //open a new file
        myfile.open(Contents[i].c_str());
        cout<<Contents[i]<<"*******opening file"<<endl;
        string line;
        if(myfile.is_open())
        {
            getline(myfile,line);
            CourtNo.push_back(atoi(line.c_str()));
            cout<<"Adding to Court numbers  "<<CourtNo[i]<<endl;
            getline(myfile,line);
            TriggerPin.push_back(atoi(line.c_str()));
            cout<<"Adding to Associated Court Pin  "<<TriggerPin[i]<<endl;
        }
        else
        {
            cout<<"could not open file"<<endl;
        }
        myfile.close();
    }
}

