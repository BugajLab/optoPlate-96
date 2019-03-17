
#include "Adafruit_TLC5947.h"
#include "Arduino.h"
#include <avr/pgmspace.h>

// How many boards do you have chained?
const uint8_t NUM_TLC5974 = 12;

const uint8_t data  = 4;
const uint8_t clock = 5;
const uint8_t latch = 6;
const uint8_t oe  = 7;  // set to -1 to not use the enable pin (its optional)

//defines numbers of channels total for all colors (288 channels for 3 col 96 well plate)
const int chanNum = 24*NUM_TLC5974;
 
//defines state of pins (0 = OFF)
uint8_t ledState[chanNum/3] = {0};

//Cycle number (for fine pulsing)
uint16_t cycNum[chanNum/3] = {0};
                           
Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch);

// Define whether individual positions will be OFF (0), in timecourse mode (1), or in constant light setting mode (2) (in flash memory, read only)  Rows: A-H. Columns: 1-12                                  
uint8_t const LEDmode[] PROGMEM ={ 
/*
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,
0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1
*/


1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

};       

                          
const uint8_t OFF = 0;
const uint8_t TIMECOURSE = 1;
const uint8_t CONST_INTENSITY = 2;
const uint8_t OFF_TIMECOURSE = 3;

                                  
//Pulse intervals (flash memory, read only)  Rows: A-H. Columns: 1-12
const uint32_t interval[] PROGMEM = {
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,
2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,	2000,


};

//Pulse widths (flash memory, read only). Rows: A-H. Columns: 1-12
uint32_t const pulse[] PROGMEM = { 
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,
};
                                  
//LED intensity, for constant intensity setting (flash memory, read only). Rows: A-H. Columns: 1-12
uint16_t const intensity[] PROGMEM = { 
 //BLUE INTENSITIES
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
 
 //RED INTENTSITIES
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,

//FAR RED INTENSITIES
1000,  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
};
                           
//number of phases in timecourse (including initial delay phase
const uint8_t totPhaseNum = 3;

//Set intensities for various phases.
uint16_t phaseOFF[3] = {0,0,0};
uint16_t phaseDELAY[3] = {0,0,4095};
uint16_t phase1int[3] = {0,100,0};
uint16_t phase2int[3] = {0,0,4095};

//array of phases
uint16_t *phases[totPhaseNum+1] = {phaseOFF, phaseDELAY, phase1int, phase2int};

//define the current phase (0-3), with 0 being OFF
uint8_t currPhase[chanNum/3] = {0};

//Time variables for pulse lengths
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
uint32_t s120 = 1000UL*120UL;

uint32_t  m3 = 60UL*1000UL*3UL;
uint32_t  m4 = 60UL*1000UL*4UL;
uint32_t  m5 =  60UL*1000UL*5UL;
uint32_t  m8 =  60UL*1000UL*8UL;
uint32_t  m9 =  60UL*1000UL*9UL;
uint32_t  m9_15 =  60UL*1000UL*9.25;
uint32_t  m9_30 =  60UL*1000UL*9.5;
uint32_t  m9_40 =  60UL*1000UL*9.66;
uint32_t  m9_50 =  60UL*1000UL*9.83;
uint32_t  m9_55 =  60UL*1000UL*9.916;
uint32_t  m10 = 60UL*1000UL*10UL;
uint32_t  m15 = 60UL*1000UL*15UL;
uint32_t  m20 = 60UL*1000UL*20UL;
uint32_t  m25 = 60UL*1000UL*25UL;
uint32_t  m30 = 60UL*1000UL*30UL;
uint32_t  m35 = 60UL*1000UL*35UL;
uint32_t  m40 = 60UL*1000UL*40UL;
uint32_t  m45 = 60UL*1000UL*45UL;
uint32_t  m50 = 60UL*1000UL*50UL;
uint32_t  m55 = 60UL*1000UL*55UL;
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

uint32_t h2  = 1000UL*60UL*60UL*2UL;
uint32_t h3  = 1000UL*60UL*60UL*3UL;
uint32_t h4  = 1000UL*60UL*60UL*4UL;
uint32_t h6  = 1000UL*60UL*60UL*6UL;
uint32_t h7  = 1000UL*60UL*60UL*7UL;
uint32_t h7_5  = 1000UL*60UL*60UL*7.5;
uint32_t h8  = 1000UL*60UL*60UL*8UL;
uint32_t h12 = 1000UL*60UL*60UL*12UL;
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

//defines timecourse for each channel as array of pointers
const uint32_t * const phaseTimes[chanNum/3][totPhaseNum] PROGMEM = {
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
{&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},  {&s0,&h48,&m10},
};

//Define constant off times for OFF_TIMECOURSE setting
const uint32_t * const off_millis[] PROGMEM ={
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
}; //H   
                                  
                                  
//Define constant on times for variable constant Red ON times
const uint32_t * const on_millis[] PROGMEM ={
&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,
&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,	&s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
&s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,  &s0,
};  

// define time that IR or Red will be constantly on after ON->OFF transition and OFF->ON transition
uint32_t *IRoffSwitch =  &m5;
uint32_t *REDonSwitch =  &s60;

//define pointers to be used in script for pointing to either a constant switch time or to the variable switch times (on_millis, offmillis)
uint32_t *offTime;
uint32_t *onTime;




//define flag to determine whther a channel has just switched to an OFF(1) or OFF (2) phase. 
uint8_t switchTo[chanNum/3] = { 
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0};
                                  
//define flag to determine if channel just switched to ON phase                                

//define if using phase intensities or variable intensities. 0 to use phase intensities, 1 to use variable.
uint8_t useVarIntensity = 0;

//define if pulsed or constant. 1 for pulsed, 0 for constant
uint8_t pulsed = 0;

//define if in test mode. If in test mode, define "factor" for how much to divide phase times by
uint8_t test = 0;

uint32_t factor = 60UL; //times change from hours to seconds

//keep track of when switched to the current phase
uint32_t lastPhaseSwitch[chanNum/3] = {0};

//use variable times for ON or OFF constant illumination when to red or IR (1 yes, 0 no)?
uint8_t varON = 0;
uint8_t varOFF = 0;

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
     s1 = (uint32_t)s1/factor;
     s5 = (uint32_t)s5/factor;
     s10 = (uint32_t)s10/factor;
    s30 = (uint32_t)s30/factor;
    s60 = (uint32_t)s60/factor;
    s120 = (uint32_t)s120/factor;
  
     m3 =  (uint32_t)m3/factor; 
     m4 =  (uint32_t)m4/factor;
     m5 =  (uint32_t)m5/factor;
     m10 = (uint32_t)m10/factor;
     m15 = (uint32_t)m15/factor;
     m20 = (uint32_t)m20/factor;
     m25 = (uint32_t)m25/factor;
     m30 = (uint32_t)m30/factor;
     m35 = (uint32_t)m35/factor;
     m40 = (uint32_t)m40/factor;
     m45 = (uint32_t)m45/factor;
     m50 = (uint32_t)m50/factor;
     m55 = (uint32_t)m55/factor;
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
     h12 = (uint32_t)h12/factor;
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
    if(mode == TIMECOURSE || mode == OFF_TIMECOURSE){
      setAll(i,phaseDELAY);
      currPhase[i] = 1;
      ledState[i] = 1;
    }
  }
  tlc.write();
}
  
  
void loop(){
  
 uint8_t changed = 0;
 unsigned long currMillis = millis();
 uint8_t phaseChanged = 0;
 
  //Identify correct illlumination phase, update LED settings
   for (uint16_t i = 0; i<chanNum/3; i++){
     uint8_t mode = pgm_read_word_near(LEDmode+i);
     
     if(mode != OFF){
       if(mode == TIMECOURSE){       //Loops to compare current time against timecourse timing, and also to hold light settings at last timepoint 
         uint32_t *phaseT = (uint32_t*)pgm_read_word_near(&phaseTimes[i][currPhase[i]-1]);         
         if (currMillis -lastPhaseSwitch[i] > *phaseT){
           lastPhaseSwitch[i] = lastPhaseSwitch[i] + *phaseT;
           if (currPhase[i] == 2){  //if phase is 2, go to 3
             currPhase[i] = 3;
             switchTo[i] = 1;
             phaseChanged = 1; //Set flag to indicate that channel has just switched from ON to OFF
           } 
           else{
             currPhase[i] = 2; //if phase is 1(delay) or 3, go to 2
             phaseChanged = 1;
             switchTo[i] = 2;
           } //set flag to indicate that channel has just been switched ON
         }
       }
       
       //Specially for OFF_timecourse
       if( mode == OFF_TIMECOURSE){       //Loops to compare current time against timecourse timing, and also to hold light settings at last timepoint 
         uint32_t *phaseT = (uint32_t*)pgm_read_word_near(&phaseTimes[i][currPhase[i]-1]);         
         if (currMillis -lastPhaseSwitch[i] > *phaseT && switchTo[i] == 0){
           if (currPhase[i] == 1){
             currPhase[i] = 2;
             lastPhaseSwitch[i] = lastPhaseSwitch[i] + *phaseT;
             phaseChanged = 1;
           }
           else if (currPhase[i] == 2){  //if phase is 2, go to 3
             currPhase[i] = 3;
             lastPhaseSwitch[i] = lastPhaseSwitch[i] + *phaseT;
             switchTo[i] = 1; //Set flag to indicate that channel has just switched from ON to OFF
             phaseChanged = 1;
           } 
       }
       }
       
      //Setting new LED settings in constant (non-pulsed) light setting
      if (!pulsed){
        if(mode == TIMECOURSE || mode == OFF_TIMECOURSE){
          if (phaseChanged){
             if (currPhase[i] == 2 && useVarIntensity){
               uint16_t blueInt = pgm_read_word_near(intensity+i);
               uint16_t redInt = pgm_read_word_near(intensity+i+96);
               uint16_t fredInt = pgm_read_word_near(intensity+i+192);
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
        else if (mode == CONST_INTENSITY){
         
            uint16_t blueInt = pgm_read_word_near(intensity+i);
            uint16_t redInt = pgm_read_word_near(intensity+i+96);
            uint16_t fredInt = pgm_read_word_near(intensity+i+192);
            uint16_t intensities[3] = {blueInt, redInt, fredInt};              
            setAll(i, intensities);
            changed = 1;
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
              if (mode == TIMECOURSE || mode == OFF_TIMECOURSE){ 
                if (currPhase[i] == 2 && useVarIntensity){
                  uint16_t blueInt = pgm_read_word_near(intensity+i);
                  uint16_t redInt = pgm_read_word_near(intensity+i+96);
                  uint16_t fredInt = pgm_read_word_near(intensity+i+192);
                  uint16_t intensities[3] = {blueInt, redInt, fredInt};
                  setAll(i, intensities);
                  changed = 1;
                }
                else{
                  setAll(i, phases[currPhase[i]]); //set all LED intensities to the current phase
                  changed = 1;        //set the "LED changed" flag to write to LEDs
                }
              }
         }
         else {
              if (currMillis-prevMillis> memPulse && ledState[i] == 1){  // if pulse time expired, turn LED OFF
                ledState[i] = 0;             //set LED flag to OFF
                changed = 1;                 //set the "LED changed" flag to write to LEDs
                setAll(i,phaseOFF);         //set LED OFF   
              }  
            } 
          }
          
          //Loops to check if LED as just turned from ON to OFF or OFF to ON. If so, keep IR or Red ON constantly, respectively.
         
         //Define constant OFF time based on setup
         if (switchTo[i] == 1){
           if (varOFF){
            offTime =  (uint32_t*)pgm_read_word_near(off_millis+i);}
           else {
            offTime =  IRoffSwitch;}
          }
        
         // Define constant ON time based on setup
         if (switchTo[i] == 2){
           if (varON){
            onTime =  (uint32_t*)pgm_read_word_near(on_millis+i);}
           else {
            onTime =  REDonSwitch;}
         }
     
         if (mode == TIMECOURSE){
           if (switchTo[i] ==1 && (currMillis-lastPhaseSwitch[i]) < *offTime){
            setAll(i,phase2int);
            changed = 1;}
           else if (switchTo[i] == 1 && (currMillis - lastPhaseSwitch[i]) > *offTime){
             switchTo[i] = 0;
             setAll(i,phaseOFF);
             changed = 1;}
           else if (switchTo[i] == 2 && (currMillis - lastPhaseSwitch[i]) < *onTime){
             if (useVarIntensity){
               uint16_t blueInt = pgm_read_word_near(intensity+i);
               uint16_t redInt = pgm_read_word_near(intensity+i+96);
               uint16_t fredInt = pgm_read_word_near(intensity+i+192);
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
   }
   
//if LED settings were updated, then write new settings to LEDs
  if (changed){
    tlc.write();
    changed = 0;
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
  //setBlue(well, bright);
  setRed(well, bright);
  //setFarRed(well, bright);
}


