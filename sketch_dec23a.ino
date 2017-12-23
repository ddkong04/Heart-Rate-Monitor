#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>

// just adding a comment

float amplifiedSignal;
float filteredSignal;

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

  amplifiedSignal = 100*analogRead(A0);
  filteredSignal = filterOneHighpass.input(filterOneLowpass.input(amplifiedSignal));

  Serial.println(analogRead(A0));


}
