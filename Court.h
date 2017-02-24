//this is the header file for the control of lights.
//each of these objects will represent the control of one light

#include <bcm2835.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "apiget.h"


//DEFINE ALL MY PINS
#define J803 RPI_V2_GPIO_P1_03
#define J805 RPI_V2_GPIO_P1_05
#define J807 RPI_V2_GPIO_P1_07
#define J808 RPI_V2_GPIO_P1_08
#define J810 RPI_V2_GPIO_P1_10
#define J811 RPI_V2_GPIO_P1_11
#define J812 RPI_V2_GPIO_P1_12
#define J813 RPI_V2_GPIO_P1_13
#define J815 RPI_V2_GPIO_P1_15
#define J816 RPI_V2_GPIO_P1_16
#define J818 RPI_V2_GPIO_P1_18
#define J819 RPI_V2_GPIO_P1_19
#define J821 RPI_V2_GPIO_P1_21
#define J822 RPI_V2_GPIO_P1_22
#define J823 RPI_V2_GPIO_P1_23
#define J824 RPI_V2_GPIO_P1_24
#define J826 RPI_V2_GPIO_P1_26
#define J829 RPI_V2_GPIO_P1_29
#define J831 RPI_V2_GPIO_P1_31
#define J832 RPI_V2_GPIO_P1_32
#define J833 RPI_V2_GPIO_P1_33
#define J835 RPI_V2_GPIO_P1_35
#define J836 RPI_V2_GPIO_P1_36
#define J837 RPI_V2_GPIO_P1_37
#define J838 RPI_V2_GPIO_P1_38
#define J840 RPI_V2_GPIO_P1_40
//DEFINE OUTPUT AND INPUT
#define output BCM2835_GPIO_FSEL_OUTP
#define input BCM2835_GPIO_FSEL_INPT

using namespace std;

class Court
{
	//my private variblbes and functions
    private:
        int CourtNo;
        bool Status;
        int AssociatedPin;
        int PinLookUpTable(int);
        vector<int> bookingID;
        vector<int> bookingTime;
        vector<int> bookingEndTime;

	public:
        //constructor for my Courts
        Court(){};
        Court(int, bool, int);
	    //getter and setter for Associated Pin
        int GetAssociatedPin() { return AssociatedPin; }
        void SetAssociatedPin(int val) { AssociatedPin = val; }
        //Getter and setter with Court no
        int GetCourtNo() { return CourtNo; }
        void SetCourtNo(int val) { CourtNo = val; }
        //getter and setter for status
        bool GetStatus() { return Status; }
        void SetStatus(bool val) { Status = val; }
        //turn the lights on and off
        void TurnLightsOn();
        void TurnLightsOff();
        int PinLookUpTable();
        //look up the courts and see if they're supposed to be on
        int LookUpCourtStatus();
        void CheckCurrentCourtStatus();
        void CheckStatus();

};

