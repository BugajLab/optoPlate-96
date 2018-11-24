
#include "Adafruit_TLC5947.h"
#include "Arduino.h"
#include <avr/pgmspace.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//SECTION 1: Variable definitions
//SECTION 1: Variable definitions
//SECTION 1: Variable definitions
///////////////////////////////////////////////////////////////////////////////////////////////// 

//DO NOT CHANGE 
//define number of LED drivers and assign microcontroller
const uint8_t NUM_TLC5974 = 12; 
const uint8_t data  = 4;
const uint8_t clock = 5;
const uint8_t latch = 6;
const uint8_t oe  = 7;  // set to -1 to not use the enable pin (its optional)

//DO NOT CHANGE
const int chanNum = 24*NUM_TLC5974; //number of channels
const uint8_t OFF = 0; //defines state variable for OFF state
uint8_t ledState[chanNum/3] = {0}; //tracks the LED state (ON or OFF)
uint32_t cycNum[chanNum/3] = {0}; //counts number of pulsing cycles
Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch); //creates LED driver object


//Define time variables for script
//Add definitions as needed, following the provided syntax
//Also make sure to add associated definition to "test mode" timing in Section 2
//SECONDS
uint32_t s0 = 0;
uint32_t s1 = 1000UL*1UL;
uint32_t s5 = 1000UL*5UL;
uint32_t s10 = 1000UL*10UL;
uint32_t s6 = 1000UL*6UL;
uint32_t s12 = 1000UL*12UL;
uint32_t s18 = 1000UL*18UL;
uint32_t s20 = 1000UL*20UL;
uint32_t s24 = 1000UL*24UL;
uint32_t s30 = 1000UL*30UL;
uint32_t s36 = 1000UL*36UL;
uint32_t s42 = 1000UL*42UL;
uint32_t s45 = 1000UL*45UL;
uint32_t s48 = 1000UL*48UL;
uint32_t s60 = 1000UL*60UL;
uint32_t s90 = 1000UL*90UL;
uint32_t s120 = 1000UL*120UL;

//MINUTES
uint32_t  m2 = 60UL*1000UL*2UL;
uint32_t  m3 = 60UL*1000UL*3UL;
uint32_t  m4 = 60UL*1000UL*4UL;
uint32_t  m5 =  60UL*1000UL*5UL;
uint32_t  m6 =  60UL*1000UL*6UL;
uint32_t  m8 =  60UL*1000UL*8UL;
uint32_t  m9 =  60UL*1000UL*9UL;
uint32_t  m9_15 =  60UL*1000UL*9.25;
uint32_t  m9_30 =  60UL*1000UL*9.5;
uint32_t  m9_40 =  60UL*1000UL*9.66;
uint32_t  m9_50 =  60UL*1000UL*9.83;
uint32_t  m9_55 =  60UL*1000UL*9.916;
uint32_t  m10 = 60UL*1000UL*10UL;
uint32_t  m13 = 60UL*1000UL*13UL;
uint32_t  m15 = 60UL*1000UL*15UL;
uint32_t  m18 = 60UL*1000UL*18UL;
uint32_t  m19 = 60UL*1000UL*19UL;
uint32_t  m19_30 = 60UL*1000UL*19.5;
uint32_t  m20 = 60UL*1000UL*20UL;
uint32_t  m25 = 60UL*1000UL*25UL;
uint32_t  m28 = 60UL*1000UL*28UL;
uint32_t  m29 = 60UL*1000UL*29UL;
uint32_t  m29_30 = 60UL*1000UL*29.5;
uint32_t  m30 = 60UL*1000UL*30UL;
uint32_t  m35 = 60UL*1000UL*35UL;
uint32_t  m40 = 60UL*1000UL*40UL;
uint32_t  m45 = 60UL*1000UL*45UL;
uint32_t  m50 = 60UL*1000UL*50UL;
uint32_t  m55 = 60UL*1000UL*55UL;
uint32_t  m58 = 60UL*1000UL*58UL;
uint32_t  m59 = 60UL*1000UL*59UL;
uint32_t  m59_30 = 60UL*1000UL*59.5;
uint32_t  m60 = 60UL*1000UL*60UL;
uint32_t  m65 = 60UL*1000UL*65UL;
uint32_t  m70 = 60UL*1000UL*70UL;
uint32_t  m75 = 60UL*1000UL*75UL;
uint32_t  m80 = 60UL*1000UL*80UL;
uint32_t  m85 = 60UL*1000UL*85UL;
uint32_t  m88 = 60UL*1000UL*88UL;
uint32_t  m89 = 60UL*1000UL*89UL;
uint32_t  m89_30 = 60UL*1000UL*89.5;
uint32_t m90 = 60UL*1000UL*90UL;
uint32_t m95 = 60UL*1000UL*95UL;
uint32_t m100 = 60UL*1000UL*100UL;
uint32_t m110 = 60UL*1000UL*110UL;
uint32_t m120 = 60UL*1000UL*120UL;
uint32_t m125 = 60UL*1000UL*125UL;
uint32_t m135 = 60UL*1000UL*135UL;

//HOURS
uint32_t h2  = 1000UL*60UL*60UL*2UL;
uint32_t h3  = 1000UL*60UL*60UL*3UL;
uint32_t h4  = 1000UL*60UL*60UL*4UL;
uint32_t h6  = 1000UL*60UL*60UL*6UL;
uint32_t h7  = 1000UL*60UL*60UL*7UL;
uint32_t h7_5  = 1000UL*60UL*60UL*7.5;
uint32_t h8  = 1000UL*60UL*60UL*8UL;
uint32_t h10 = 1000UL*60UL*60UL*10UL;
uint32_t h12 = 1000UL*60UL*60UL*12UL;
uint32_t h14 = 1000UL*60UL*60UL*14UL;
uint32_t h16 = 1000UL*60UL*60UL*16UL;
uint32_t h18 = 1000UL*60UL*60UL*18UL;
uint32_t h19 = 1000UL*60UL*60UL*19UL;
uint32_t h20 = 1000UL*60UL*60UL*20UL;
uint32_t h22 = 1000UL*60UL*60UL*22UL;
uint32_t h24 = 1000UL*60UL*60UL*24UL;
uint32_t h26 = 1000UL*60UL*60UL*26UL;
uint32_t h30 = 1000UL*60UL*60UL*30UL;
uint32_t h36 = 1000UL*60UL*60UL*36UL;
uint32_t h42 = 1000UL*60UL*60UL*42UL;
uint32_t h48 = 1000UL*60UL*60UL*48UL;

// Define whether individual LED positions will be OFF (0) or ON (1). Formatted like 96-well plate
uint8_t const LEDmode[] PROGMEM ={ 
// 1   2   3   4   5   6   7   8   9  10  11  12
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
};       


//PHASE DEFINITIONS//
//PHASE DEFINITIONS//
//PHASE DEFINITIONS//

//Define number of phases in timecourse (including initial delay phase)
//script assumes 3 phases
const uint8_t totPhaseNum = 3;

//define phase timing using time variables from above
 const uint32_t * const phaseTimes[chanNum/3][totPhaseNum] PROGMEM = {
{&s0,&h12,&h48},  {&s0,&h8,&h48}, {&h48,&h48,&h48}, {&h48,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48},
{&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48},
{&h12,&h48,&h48}, {&h12,&h48,&h48}, {&h12,&h48,&h48}, {&h12,&h48,&h48}, {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},
{&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&h48,&h48,&h48},
{&h8,&h48,&h48},  {&h8,&h48,&h48},  {&h8,&h48,&h48},  {&h8,&h48,&h48},  {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48}, {&h14,&h48,&h48},
{&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48}, {&h10,&h48,&h48},
{&h4,&h48,&h48},  {&h4,&h48,&h48},  {&h4,&h48,&h48},  {&h4,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},  {&h6,&h48,&h48},
{&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},  {&s0,&h48,&h48},
};

//Indicate whether using global (phase) intensities or individual(variable) intensities per each LED.
//0 to use global intensities, 1 to use intdividual.  
//Can do this for ON intensities (define for ON pulse, OFF pulse), OFF intensities

uint8_t useVarOnPulseIntensity = 0;
uint8_t useVarOffPulseIntensity = 0;
uint8_t useVarOffPhaseIntensity = 0;

//Define illumination intensities by phase (global settings). 
//{blue,red,far-red}
//levels: 0-4095
uint16_t phaseOFF[3] = {0,0,0};
uint16_t phaseDELAY[3] = {0,0,4095};
uint16_t phase1int[3] = {0,2000, 0};
uint16_t phase2int[3] = {0,0,4095};

//Define illumination intensities by individual LEDs
//Define intensities for the ON pulse (ON phase) of illumination (levels 0-4095)
uint16_t const intensityOnPulse[] PROGMEM = { 
//BLUE INTENSITIES
1000,  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
  
//RED INTENTSITIES
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 
  
//FAR RED INTENSITIES
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,    
};

//Define intensities for the "OFF" pulse (ON phase) of illumination (levels 0-4095) 
const uint16_t intensityOffPulse[] PROGMEM = { 
//BLUE INTENSITIES
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    
   
//RED INTENTSITIES
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 

//FAR RED INTENSITIES
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
  };

//Define intensities for the OFF phase of illumination (levels 0-4095) 
const uint16_t intensityOffPhase[] PROGMEM = { 
   //BLUE INTENSITIES
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    
   
   //RED INTENTSITIES
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      
  
  //FAR RED INTENSITIES
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  4095,  4095, 4095, 4095, 4095, 4095,  4095,  4095, 4095, 4095, 4095, 4095,
  };

//DO NOT CHANGE
uint16_t *phases[totPhaseNum+1] = {phaseOFF, phaseDELAY, phase1int, phase2int}; ////array of phases
uint8_t currPhase[chanNum/3] = {0}; //defines the current phase (0-3), with 0 being OFF
uint8_t switchTo[chanNum/3] = {
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0};                             
uint32_t lastPhaseSwitch[chanNum/3] = {0}; //keep track of when switched to the current phase


//PULSE DEFINITIONS//
//PULSE DEFINITIONS//
//PULSE DEFINITIONS//

//Define if LEDs are pulsed or constant illumination within phases. 1 for pulsed, 0 for constant. 
//Recommended to use pulsed for experiments, constant for "test mode"
uint8_t pulsed = 1;

//Define pulse intervals in ms (period of pulses) 
const uint32_t interval[] PROGMEM = {
3500,  3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
};

//define pulse widths in ms
uint32_t const pulse[] PROGMEM = { 
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
};
                          

//Define pulse width (ms) of illumination during the "OFF" pulse (ON phase). Should be less than (interval-pulse)
uint32_t const onPhaseOffPulseW[96] PROGMEM= {
1000,  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
};

                           
//PHASE TRANSITION DEFINITIONS//
//PHASE TRANSITION DEFINITIONS//
//PHASE TRANSITION DEFINITIONS//

//Define whether constant illumination time post-transition is defined globally or individually for each LED set 
//1 for individual (variable), 0 for global
uint8_t varON = 0;
uint8_t varOFF = 0;

//define global times of constant illumination post-transition (using time variables previously defined) 
uint32_t *off_millisGlobal =  &s0; //after ON->OFF transition
uint32_t *on_millisGlobal =  &s0; //after OFF->ON transition


//define variable times of constant illumination after ON->OFF transition (using time variables previously defined) 
const uint32_t * const off_millis[] PROGMEM ={ 
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0
}; 
                                                                    
//define variable times of constant illumination after OFF->ON transition (using time variables previously defined) 
const uint32_t * const on_millis[] PROGMEM ={ 
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0
};  

//DO NOT CHANGE
// pointers to (on_millis/Global, off_millis/Global)
uint32_t *offTime; 
uint32_t *onTime;

//TEST MODE DEFINITION//
//TEST MODE DEFINITION//
//TEST MODE DEFINITION//

//define if in test mode, which speeds up experiments. If in test mode, define "factor" for how much to divide phase times by
uint8_t test = 0;
uint32_t factor = 3600UL; //factor = 3600 scales experiement down from hours to seconds.

//FAN SPEED//
//FAN SPEED//
//FAN SPEED//

//define fan speed. levels: ~100-255 (255 is max speed)
uint8_t fanSpeed = 255;

/////////////////////////////////////////////////////////////////////////////////////////////////
//SECTION 2: Setup
//SECTION 2: Setup
//SECTION 2: Setup
/////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  tlc.begin();
  
  //set initial LED states to 0
  for (int i = 0; i < chanNum/3; i++){
    setAll(i,phaseOFF);
    cycNum[i] = 0;}
    tlc.write();
  
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, HIGH);
    }
    
  //if in test mode, divide phase times by defined factor amount to visualize entire timecourse
  if (test){
    pulsed = 0;
    
     s1 = (uint32_t)s1/factor;
     s5 = (uint32_t)s5/factor;
     s10 = (uint32_t)s10/factor;
    s30 = (uint32_t)s30/factor;
    s60 = (uint32_t)s60/factor;
    s90 = (uint32_t)s90/factor;
    s120 = (uint32_t)s120/factor;
  
     m2 =  (uint32_t)m2/factor; 
     m3 =  (uint32_t)m3/factor; 
     m4 =  (uint32_t)m4/factor;
     m5 =  (uint32_t)m5/factor;
     m6 =  (uint32_t)m6/factor;
     m8 =  (uint32_t)m8/factor;
     m9 =  (uint32_t)m9/factor;
     m9_30 =  (uint32_t)m9_30/factor;
     m10 = (uint32_t)m10/factor;
     m13 = (uint32_t)m13/factor;
     m15 = (uint32_t)m15/factor;
     m18 = (uint32_t)m18/factor;
     m19 = (uint32_t)m19/factor;
     m19_30 = (uint32_t)m19_30/factor;
     m20 = (uint32_t)m20/factor;
     m25 = (uint32_t)m25/factor;
     m28 = (uint32_t)m28/factor;
     m29 = (uint32_t)m29/factor;
     m29_30 = (uint32_t)m29_30/factor;
     m30 = (uint32_t)m30/factor;
     m35 = (uint32_t)m35/factor;
     m40 = (uint32_t)m40/factor;
     m45 = (uint32_t)m45/factor;
     m50 = (uint32_t)m50/factor;
     m55 = (uint32_t)m55/factor;
     m58 = (uint32_t)m58/factor;
     m59 = (uint32_t)m59/factor;
     m59_30 = (uint32_t)m59_30/factor;
     m60 = (uint32_t)m60/factor;
     m65 = (uint32_t)m65/factor;
     m70 = (uint32_t)m70/factor;
     m75 = (uint32_t)m75/factor;
     m80 = (uint32_t)m80/factor;
     m85 = (uint32_t)m85/factor;
     m90 = (uint32_t)m90/factor;
     m95 = (uint32_t)m95/factor;
     m100 = (uint32_t)m100/factor;
     m110 = (uint32_t)m110/factor;
     m120 =(uint32_t)m120/factor;
     m125 =(uint32_t)m125/factor;
     m135 =(uint32_t)m135/factor;
    
    h2 =  (uint32_t)h2/factor;
     h3 =  (uint32_t)h3/factor;
     h4 =  (uint32_t)h4/factor;
     h6 =  (uint32_t)h6/factor;
     h7 = (uint32_t)h7/factor;
     h7_5 = (uint32_t)h7_5/factor;
     h8 =  (uint32_t)h8/factor;
     h10 = (uint32_t)h10/factor;
     h12 = (uint32_t)h12/factor;
     h14 = (uint32_t)h14/factor;
     h16 = (uint32_t)h16/factor;
     h18 = (uint32_t)h18/factor;
     h19 = (uint32_t)h19/factor;
     h20 = (uint32_t)h20/factor;
     h22 = (uint32_t)h22/factor;
     h24 = (uint32_t)h24/factor;
     h26 = (uint32_t)h26/factor;
     h30 = (uint32_t)h30/factor;
     h36 = (uint32_t)h36/factor;
     h42 = (uint32_t)h42/factor;
     h48 = (uint32_t)h48/factor;
     
  }

        
    
    
    
  //set initial LED states to first pulse intensity
  for (int i = 0; i < chanNum/3; i++){
    uint8_t mode = pgm_read_word_near(LEDmode+i);
    setAll(i,phaseDELAY);
    currPhase[i] = 1;
    ledState[i] = 1; 
    }
  tlc.write();

  //set the pin speed
  pinMode(11,OUTPUT);
  analogWrite(11, fanSpeed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//SECTION 3: Loop (illumination)
//SECTION 3: Loop (illumination)
//SECTION 3: Loop (illumination)
/////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){
 uint8_t changed = 0;
 unsigned long currMillis = millis();
 uint8_t phaseChanged = 0;
 
  //Identify correct illlumination phase, update LED settings
   for (uint16_t i = 0; i<chanNum/3; i++){
     uint8_t mode = pgm_read_word_near(LEDmode+i);
     
     if(mode != OFF){  //Loops to compare current time against timecourse timing, and also to hold light settings at last timepoint 
         uint32_t *phaseT = (uint32_t*)pgm_read_word_near(&phaseTimes[i][currPhase[i]-1]);         
         if (currMillis -lastPhaseSwitch[i] > *phaseT){
           lastPhaseSwitch[i] = lastPhaseSwitch[i] + *phaseT;
           if (currPhase[i] == 2){  //if phase is 2, go to 3
             currPhase[i] = 3;
             switchTo[i] = 1;
             phaseChanged = 1; //Set flag to indicate that channel has just switched from ON to OFF
           } 
           else{
             currPhase[i] = 2;      //if phase is 1(delay) or 3, go to 2
             phaseChanged = 1;
             if(!test & pulsed){
               switchTo[i] = 2; //set flag to indicate that channel has just been switched ON
             }
           } 
         }
              
       
      //Setting new LED settings in constant (non-pulsed) light setting
      if (!pulsed){
          if (phaseChanged){
             if (currPhase[i] == 2 && useVarOnPulseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOnPulse+i);
                  uint16_t redInt = pgm_read_word_near(intensityOnPulse+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOnPulse+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else if (currPhase[i] == 3 && useVarOffPhaseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOffPhase+i);
                  uint16_t redInt = pgm_read_word_near(intensityOffPhase+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOffPhase+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else if (currPhase[i] == 1 && useVarOffPhaseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOffPhase+i);
                  uint16_t redInt = pgm_read_word_near(intensityOffPhase+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOffPhase+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
             else{
               setAll(i,phases[currPhase[i]]);
               changed = 1;
             }
           }  
      }      
      
     //Setting new LED settings in pulsed light setting
      if (pulsed){
         uint32_t memInterval = pgm_read_dword(interval+i);
         uint32_t memPulse = pgm_read_dword(pulse+i);
         uint32_t prevMillis = (uint32_t)cycNum[i]*memInterval;
    
         if (currMillis-prevMillis > memInterval && ledState[i] == 0) { //if interval time expired, turn LED ON
              ledState[i] = 1;          //set LED flag to ON
              cycNum[i] = cycNum[i]+1;  //increment cycle 
                if (currPhase[i] == 2 && useVarOnPulseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOnPulse+i);
                  uint16_t redInt = pgm_read_word_near(intensityOnPulse+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOnPulse+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else if (currPhase[i] == 3 && useVarOffPhaseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOffPhase+i);
                  uint16_t redInt = pgm_read_word_near(intensityOffPhase+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOffPhase+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else if (currPhase[i] == 1 && useVarOffPhaseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOffPhase+i);
                  uint16_t redInt = pgm_read_word_near(intensityOffPhase+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOffPhase+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else{
                  setAll(i,phases[currPhase[i]]);
                  changed = 1;
             }
         }
         else {
              if (currMillis-prevMillis> memPulse && ledState[i] == 1){  // if pulse time expired, turn LED OFF
                if(!useVarOffPulseIntensity){
                  ledState[i] = 0;             //set LED flag to OFF
                  changed = 1;                 //set the "LED changed" flag to write to LEDs
                  setAll(i,phaseOFF);         //set LED OFF   
                }
                else if(useVarOffPulseIntensity){
                  uint32_t frOffTime = pgm_read_dword(onPhaseOffPulseW+i);
                  if(currPhase[i] == 2 && (currMillis-prevMillis-memPulse) < frOffTime){
                    ledState[i] = 1; 
                    uint16_t blueInt = pgm_read_word_near(intensityOffPulse+i);
                    uint16_t redInt = pgm_read_word_near(intensityOffPulse+i+96);
                    uint16_t fredInt = pgm_read_word_near(intensityOffPulse+i+192);
                    uint16_t intensities[3] = {blueInt, redInt, fredInt};
                    setAll(i, intensities);
                    changed = 1;
                  }
                  else{
                    ledState[i] = 0;             //set LED flag to OFF
                    changed = 1;                 //set the "LED changed" flag to write to LEDs
                    setAll(i,phaseOFF);         //set LED OFF 
                  }
                }
            }
          }
      }
            
          
//Loops to check if LED as just turned from ON to OFF or OFF to ON. If so, keep IR or Red ON constantly, respectively. 
         //Define constant OFF time based on Section 1
         if (switchTo[i] == 1){
           if (varOFF){
            offTime =  (uint32_t*)pgm_read_word_near(off_millis+i);}
           else {
            offTime =  off_millisGlobal;}
          }
        
         // Define constant ON time based on Section 1
         if (switchTo[i] == 2){
           if (varON){
            onTime =  (uint32_t*)pgm_read_word_near(on_millis+i);}
           else {
            onTime =  on_millisGlobal;}
         }
 
         if (switchTo[i] ==1 && (currMillis-lastPhaseSwitch[i]) < *offTime){
           if (useVarOffPhaseIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensityOffPhase+i);
                  uint16_t redInt = pgm_read_word_near(intensityOffPhase+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensityOffPhase+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
            }
            else{
                  setAll(i,phase2int);
                  changed = 1;}
            }
   
         else if (switchTo[i] == 1 && (currMillis - lastPhaseSwitch[i]) > *offTime){
             switchTo[i] = 0;
             setAll(i,phaseOFF);
             changed = 1;}
         else if (switchTo[i] == 2 && (currMillis - lastPhaseSwitch[i]) < *onTime){
             if (useVarOnPulseIntensity){
               uint16_t blueInt = pgm_read_word_near(intensityOnPulse+i);
               uint16_t redInt = pgm_read_word_near(intensityOnPulse+i+96);
               uint16_t fredInt = pgm_read_word_near(intensityOnPulse+i+192);
               uint16_t intensities[3] = {blueInt, redInt, fredInt};
               setAll(i, intensities);
               changed = 1;}
             else{
               setAll(i,phase1int);
               changed = 1;}
           }
           else if (switchTo[i] == 2 && (currMillis - lastPhaseSwitch[i]) > *onTime){
             switchTo[i] = 0;
             setAll(i,phaseOFF);
             ledState[i] = 0;
             changed = 1;}
     }
   }
   
//if LED settings were updated, then write new settings to LEDs
  if (changed){
    tlc.write();
  }
}



//FUNCTIONS to control LED colors
void setBlue(uint16_t well, uint16_t *bright){
  uint16_t bluePosition = (uint16_t)((int)(well/12) + 8*(well%12));
  tlc.setPWM(bluePosition, *bright);   //Set Blue
}

void setRed(uint16_t well, uint16_t *bright){
  uint16_t redPosition = (uint16_t)((int)(well/12) + 8*(well%12)+96);
  tlc.setPWM(redPosition, *(bright+1));   //Set Red
}

void setFarRed(uint16_t well, uint16_t *bright){
  uint16_t fRedPosition = (uint16_t)(well+192);
  tlc.setPWM(fRedPosition, *(bright+2));   //Set Far-red
}

void setAll(uint16_t well, uint16_t *bright){
  setBlue(well, bright);
  setRed(well, bright);
  setFarRed(well, bright);
}


