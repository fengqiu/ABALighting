#include "Court.h"

//first we have the constructor
Court::Court(int No, bool stats,int Pin)
{
	CourtNo=No;
	Status=stats;
	AssociatedPin=PinLookUpTable(Pin);
	//set pin to output
	// Set the pin to be an output
	cout<<"setting pin to output"<<endl;
    bcm2835_gpio_fsel(AssociatedPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_set_pud(AssociatedPin,BCM2835_GPIO_PUD_DOWN  );
	//initiate with the lights off
	TurnLightsOff();
}
void Court::CheckStatus()
{
    uint8_t pin = bcm2835_gpio_lev(AssociatedPin);
    if(pin)
    {
        cout<<AssociatedPin<<": Pin set High"<<endl;
        bcm2835_gpio_clr(AssociatedPin);
    }
}
//here are the real functions
void Court::TurnLightsOn()
{
	//run the turn lights on function here
	cout<<"Turning court: "<<CourtNo<<" On"<<endl;
	//lets try turn a court on
    bcm2835_gpio_write(AssociatedPin,HIGH);
    uint8_t pin = bcm2835_gpio_lev(AssociatedPin);
    if(pin)
    {
        cout<<AssociatedPin<<": Pin set high"<<endl;
    }
    Status=1;

}
void Court::TurnLightsOff()
{
    // turn the lights off
    cout<<"Turning court: "<<CourtNo<<" off"<<endl;
    // Turn it on
    // remember, for a darlington array we have inverse logic.
    bcm2835_gpio_write(AssociatedPin,LOW);
    bcm2835_gpio_clr(AssociatedPin);
    uint8_t pin = bcm2835_gpio_lev(AssociatedPin);
    if(!pin)
    {
        cout<<AssociatedPin<<": pin set low"<<endl;
    }
    Status=0;

}
int Court::PinLookUpTable(int Pin)
{
    //look up table for the pin number
    switch(Pin)
    {
        case 3:
            return J803;
            break;
        case 5:
            return J805;
            break;
        case 7:
            return J807;
            break;
        case 8:
            return J808;
            break;
        case 10:
            return J810;
            break;
        case 11:
            return J811;
            break;
        case 12:
            return J812;
            break;
        case 13:
            return J813;
            break;
        case 15:
            return J815;
            break;
        case 16:
            return J816;
            break;
        case 18:
            return J818;
            break;
        case 19:
            return J819;
            break;
        case 21:
            return J821;
            break;
        case 22:
            return J822;
            break;
        case 23:
            return J823;
            break;
        case 24:
            return J824;
            break;
        case 26:
            return J826;
            break;
        case 29:
            return J829;
            break;
        case 31:
            return J831;
            break;
        case 32:
            return J832;
            break;
        case 33:
            return J833;
            break;
        case 35:
            return J835;
            break;
        case 36:
            return J836;
            break;
        case 37:
            return J837;
            break;
        case 38:
            return J838;
            break;
        case 40:
            return J840;
            break;

        default:
            cout<<"Wrong Pin Assignment!!!!!"<<endl;
            return 1;
            break;
    }
}
int Court::LookUpCourtStatus()
{
    //In this function we will look up the court status
    //Building name of file
    //returning 1 indicates that a resync is needed.
    string CourtStatusName;
    CourtStatusName="Court"+to_string(CourtNo)+"Bookings";
    //open the file containing all the court booking information
    ifstream myFile(CourtStatusName);
    bookingEndTime.clear();
    bookingID.clear();
    bookingTime.clear();
    if(myFile.is_open())
    {
        //setting count
        while(myFile.good())
        {
            //loop through my file and get all the csv information
            string line;
            getline(myFile,line);
            //make sure the line isn't empty
            if (line!="")
            {
                stringstream newline(line);
                for (int i=0;i<4;i++)
                {
                    string newValueCSV;
                    getline(newline,newValueCSV,',');

                    switch(i)
                    {
                        case 0:
                            {
                                bookingID.push_back(atoi(newValueCSV.c_str()));
                                //cout<<"Placing this in bookings id "<<newValueCSV<<endl;
                                break;
                            }

                        case 1:
                            {
                                if (!(atoi(newValueCSV.c_str())==CourtNo))
                                {
                                    //Throw an error
                                    //call recalibrate file
                                    cout<<CourtNo<<" :"<<"Wrong court assigned to bookings file, re-sync in progress"<<endl;
                                    bookingEndTime.clear();
                                    bookingID.clear();
                                    bookingTime.clear();
                                    myFile.close();
                                    //resyncs the court file
                                    apiget ResyncAPI(CourtNo);
                                    ResyncAPI.getAPIinformation();
                                    return 1;
                                }
                                break;
                            }
                        case 2:
                            {
                                //cout<<"Placing this in bookings time "<<newValueCSV<<endl;
                                bookingTime.push_back(atoi(newValueCSV.c_str()));
                                break;
                            }
                        case 3:
                            {
                                int DurationMinutes=atoi(newValueCSV.c_str());
                                int endTime=bookingTime.back()+(DurationMinutes*60);
                                bookingEndTime.push_back(endTime);
                                //cout<<"Placing this in bookings duration "<<endTime<<endl;
                                break;
                            }
                        default:
                            cout<<"well this ain't good"<<endl;
                            break;

                    }
                }
            }
        }
        //now we've got everything we'll need to turn lights and shit on this'll be done in another function
    }
    myFile.close();
    return 0;
}
void Court::CheckCurrentCourtStatus()
{
    //in this function we will check what the current court status should be, if it is not we will correct it.
    time_t CurrentTime;
    time(&CurrentTime);
    cout<<"Current time in seconds after epoch: "<<CurrentTime<<endl;
    //compare time
    bool TurnLightOn=false;
    //scan through the whole array and see if our time falls within any booking start/end times
    for(unsigned int i=0;i<bookingEndTime.size();i++)
    {
        if ((CurrentTime>bookingTime[i]) & (CurrentTime<bookingEndTime[i]))
        {
            TurnLightOn=true;
        }
    }
    //if right now we're within a start/end time turn lights on
    if(TurnLightOn)
    {
        TurnLightsOn();
    }
    //else turn lights off
    else
    {
        TurnLightsOff();
    }
}

