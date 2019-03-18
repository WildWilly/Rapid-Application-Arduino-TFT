// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFT//lcd.h FOR SETUP.
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Store:   http://dx.com


//Arduino IDE: 1.6.9
// Board: Arduino UNO R3 Clone Master, Arduino Nano Slave
#include <EEPROM.h>
#include <Wire.h> //I2C library
#include <TouchScreen.h>
#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFT//lcd.h> // Hardware-specific library



/*****************HARDWARE SPECIFIC TO THE OPEN SMART TFT **********************************************
Manufacturer: Open-Smart
width 400
height 240
identifier: IL9341
https://www.dx.com/p/open-smart-touch-screen-expansion-shield-w-touch-pen-for-arduino-2080038
*/



#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//***********************************************//
// If you use OPEN-SMART TFT breakout board                 //
// Reconmmend you to add 5V-3.3V level converting circuit.
// Of course you can use OPEN-SMART UNO Black version with 5V/3.3V power switch,
// you just need switch to 3.3V.
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
//----------------------------------------|
// TFT Breakout  -- Arduino UNO / Mega2560 / OPEN-SMART UNO Black
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define WHITE   0xFFFF

#define NodeAddressSlave 8  // Change this unique address for each I2C slave node
#define NodeAddressMaster 9 //address of the I2C master node
#define NumberofTextBoxes 10
#define NumberofButtons 40

#define TS_LEFT 885
#define TS_RT  182
#define TS_TOP 932
#define TS_BOT 140

//uint8_t Orientation = 0;    //PORTRAIT
uint16_t g_identifier;
uint16_t ButtonPos[NumberofButtons]; //Store EEPROM index for the button is stored in this variable.
uint16_t textBoxPos[NumberofTextBoxes]; //Store EEPROM index for the button is stored in this variable.

uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
//uint8_t SwapXY = 0;
 
 uint8_t SelectedIndex;
 uint8_t index=0;
 uint8_t buttonClicked;
 uint16_t test;


uint8_t Flag;
uint16_t Pressure;
uint16_t TimeElapsed;
uint8_t buttCount=0;
uint8_t TextBoxCount=0;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 250);
TSPoint tp;

#define MINPRESSURE 1
#define MAXPRESSURE 1000

struct INITSCREEN //5 bytes
       {
        uint8_t type;
        uint8_t index;
        uint8_t rotation;
        uint16_t backColor;
       };

struct BUTTON //13 bytes
      {
        uint8_t type;
        uint8_t index;
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
        uint16_t backColor;
        bool fill;
      
      };
struct TEXTOJECT //10 bytes
      {
        uint8_t type;
        uint8_t index;
        uint16_t x;
        uint16_t y;
        uint8_t fontSize;
        uint16_t fontColor;
        uint8_t StrngLen;
       
      };
struct TEXTBOX //15 bytes
      {
        uint8_t type;//1 byte
        uint8_t index;//1 byte
        uint16_t x;//2 byte
        uint16_t y;//2 byte
        uint16_t w;//2 byte
        uint16_t h;//2 byte
        uint16_t backColor;//2 byte
        uint8_t BorderStyle;//1 byte
        uint16_t BorderColor;//2 byte
      };
//declare structure objects
static BUTTON butt={};
static TEXTOJECT txtObj={};  
static INITSCREEN Screen={};
static TEXTBOX txtBox={};
//**********************************************************************************************



void setup(void) {
  Serial.begin(9600);

    static uint16_t identifier;
    //    tft.reset();                 //we can't read ID on 9341 until begin()
    g_identifier = tft.readID(); //
    if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
    if (g_identifier == 0xFFFF) g_identifier = 0x9341; // serial
//    g_identifier = 0x9329;                             // force ID
	
tft.begin(g_identifier);
Wire.begin(NodeAddressSlave);                // join i2c bus with address #8
Wire.onReceive(receiveEvent); // register event
Wire.onRequest(requestEvent); // register event

  DrawScreen();
 EEPROM.get(ButtonPos[0],butt);

}

void loop(void) 
{
 touchDetect();

}
