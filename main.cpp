/*
 * untitled.cxx
 *
 * Copyright 2015  <pi@raspberrypi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <iostream>
#include <bcm2835.h>
#include "functions.h"
using namespace std;
int main(int argc, char **argv)
{
    //initialising the GPIO
    cout<<"Program Starting"<<endl;
	if (!bcm2835_init())
    {
        cout<<"Fuck me BCM didn't init"<<endl;
        return 1;
    }
    //read the config file
	ReadConfig myConfig ("Courts");
	//generate a vector of court objects based on the number of courts in config files
    vector<Court> myCourts = GenerateCourts(myConfig);
    //generates a vector of apiget objects based on the number of courts in the config file
    vector<apiget> myAPIs = GenerateAPI(myConfig);
        // wait a bit
    for (unsigned int i=0;i<myCourts.size();i++)
    {
        myAPIs[i].getAPIinformation();
        myCourts[i].TurnLightsOn();
        bcm2835_delay(500);
        myCourts[i].TurnLightsOff();
    }
    while(1)
    {
        for (unsigned int i=0;i<myCourts.size();i++)
        {
            myAPIs[i].getAPIinformation();
            bcm2835_delay(500);
            //myCourts[i].CheckStatus();
            myCourts[i].CheckCurrentCourtStatus();
            myCourts[i].LookUpCourtStatus();
        }
    }
	return 0;
}

