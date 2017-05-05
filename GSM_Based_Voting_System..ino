#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <GSM.h>
#define PINNUMBER "1234"

const int chipSelect = 4;





LiquidCrystal mylcd(10,11,6,5,4,3);
GSM gsmAccess;
GSMVoiceCall vcs;
int vote=0;
char numtel[20];

void setup()
{
 
  Serial.begin(9600);


  Serial.println("GSM Based Voting system");
  mylcd.print("GSM Based Voting system");


  boolean notConnected = true;
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
 
  while (notConnected)
  {
    if (gsmAccess.begin("")==GSM_READY){
      notConnected = false;
      Serial.println("Terminal Activated");
      mylcd.clear;
      mylcd.print("Terminal Activated");}
    else
    {
      Serial.println("Not connected")
      mylcd.clear;
      mylcd.print("Not conneccted");
      delay(1000);
    }
  }

  // This makes sure the modem correctly reports incoming events
  vcs.hangCall();

  Serial.println("Waiting for a Vote");
   mylcd.print("Waiting for vote");
}
void loop()
{  File dataFile = SD.open("voteResult.txt", FILE_WRITE)
  // Check the status of the voice call
  switch (vcs.getvoiceCallStatus())
  {
    case IDLE_CALL: // Nothing is happening

      break;

    case RECEIVINGCALL: // Yes! Someone is calling us

      Serial.println("VOTED !!!");
      mylcd.clear();
      mylcd.print("Voted from:");
      vcs.retrieveCallingNumber(numtel, 20);
      Serial.print("Voted From the Number:");
      Serial.println(numtel);
       mylcd.print(numtel);
      vote++;
       dataFile.println(vote);

      
      break;

    
  }
  delay(1000);
  if (Serial.read()=='\n'){
  Serial.println("number of Votes:");
  Serial.println(vote);
  }
}

