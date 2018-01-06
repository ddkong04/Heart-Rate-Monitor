#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>

float amplifiedSignal; // amplified signal
float filteredSignal;  // filtered signal

int threshold = 5; // start the loop when the value is above 50
int heartbeatCount = 0; // heartbeat counter
int bpm; // beats per minute
int maxHB = 5; // total number of heartbeats to calculate the heartrate
float startTime; // starting time
float stopTime; // stopping time
bool startprog = false; // start the prog when the heartbeat value is above the threshold value


void setup() {
  Serial.begin(9600);
}


// filter out frequencies below 1 Hz.
float highFilterFrequency = 1;

// create a highpass filter that only keeps frequencies above highFilterFrequency
FilterOnePole filterOneHighpass( HIGHPASS, highFilterFrequency );

// filters out frequenceies greater than 3 Hz.
float lowFilterFrequency = 3;

// create a lowpass filter that only keeps frequencies below lowFilterFrequency
FilterOnePole filterOneLowpass(LOWPASS, lowFilterFrequency);


void loop() {

//The next line applies a band pass filter to the signal

  amplifiedSignal = 10*analogRead(A0);
  filteredSignal = filterOneHighpass.input(filterOneLowpass.input(amplifiedSignal));
  
  // check if there's a heartbeat
  if (filteredSignal > threshold)
    startprog = true;
  else if (startprog == true && filteredSignal < threshold)
  {
    heartbeatCount+=1;
    startprog = false;
    if (heartbeatCount == 1)
      startTime = millis()/1000.0;
    else if (heartbeatCount == maxHB)
    {
      stopTime = millis()/1000.0;
      bpm = 60*(maxHB-1)/(stopTime-startTime);
      Serial.print("Your heartrate is : ");
      Serial.print(bpm);
      Serial.println(" bpm");
      heartbeatCount = 0;
    }
  }
}

  //Serial.println(analogRead(A0));
  //Serial.println(filteredSignal);

}
