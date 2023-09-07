//Max ~= 300, 500 if pushing hard and all closed


//Pressure
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
//Midi
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
//Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Initialisations
Adafruit_BMP280 bmp1;
Adafruit_BMP280 bmp2;
Adafruit_SSD1306 display(128, 32, &Wire, -1); //Width, Height, Wire, ?
Adafruit_USBD_MIDI usb_midi;
Adafruit_USBD_CDC USBSer1;

MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

//Global
bool panikMode = false;
int mainVolume = 100;             /*display */
bool volChange = false;


//Pressure
float pressureDiff;             /*display */
bool bellowsMode = false;         /*display */
const int defaultPressureSensitivity = 40;
int pressureSensitivity = defaultPressureSensitivity;    /*display */
int pressureZero = 25;            /*display somewhere*/ //Lower bound
float currentPressure = 0;         //Raw reading mapped 0-250
int pressureVelocity = 0;         //currentPressure mapped 0-127, value sent to MIDI
bool pressureConnected = false;

//Envelope
float filter = 0.1;
float nfilter;

//Display
byte dispMode = 0;

//KB
byte fingers[5] = {0, 0, 0, 0, 0};
byte currentlyOn[5] = {0, 0, 0, 0, 0};
byte currentlyCount = 0;


//Bass
byte bassOn[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int keyModifier = 0;
uint16_t bassList[3] = {0, 0, 0};
uint16_t bassCurrentlyOn[3] = {0, 0, 0};
bool bassSent[3] = {0, 0, 0};
byte bassOff[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};





void setup() {
  pinMode(25, OUTPUT);

  Wire.setSDA(20);
  Wire.setSCL(21);
  Wire.begin();

  nfilter = 1 - filter;

  setup_Midi();               //Accord_Midi
  calibratePressureSensor();  //Accord_Pressure
  setup_KB();                 //Accord_KB
  setup_Bass();               //Accord_Bass
  setup_Display();            //Accord_Display
}



int maxx = 0;
void loop() {
  if (pressureConnected)  {
    scan_Pressure();
  }  
  scan_KB();
  midi_stuff();
  display_stuff();

  delay(5); //8.0 CPS = 480 BPM = 16ms @ 1/32
}
