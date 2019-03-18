//i2c Master(UNO)
#include <Wire.h>
#define NodeAddressSlave 8  // Change this unique address for each I2C slave node
#define NodeAddressMaster 9 //address of the I2C master node
char tmpChar[10];
uint8_t GlobalNumberWidth;
uint8_t debounce=0;
uint16_t ControlCount;
byte ButtonSelected;
struct TRANSMIT
{
  uint8_t object;
  char  message[32];
};

//***********************************************************************************************************
void setup()
{
  Wire.begin(NodeAddressMaster);
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop()
{
  if(ControlCount==500)
    {
   
    Wire.requestFrom(NodeAddressSlave,1); //every thousand itterations make request. Better than a delay
    ControlCount=0;
    }
  while(Wire.available())
    {
      ButtonSelected = Wire.read();
     
      if(ButtonSelected>0 && debounce==0 )
    
        {
        debounce=1;
        switch (ButtonSelected)
          {
          case 7: //button object #7
          EchoButton("Button 7",2);//transmit to text box object #2
          break;
          case 8://button object #8
          long ExampleNumber=millis();
          //itoa(ExampleNumber,tmpChar,10);//convert integer to char array
          ltoa(ExampleNumber,tmpChar,10);//convert long to char array
          EchoButton(tmpChar,3);//transmit to text box object #3
          break;
          
          }
        delay(250);
        debounce=0;
        }
      
    }
  
  ControlCount++;
}

void EchoButton(char* Message,byte button)
{
 
  TRANSMIT transmit={}; //initialize structure
  strcpy(transmit.message,Message);
  transmit.object=button; //Select object number to identify which text box to print to.
  uint8_t structSize = strlen(transmit.message);
  Wire.beginTransmission(NodeAddressSlave);
 //this structure will identify the taget text box and the message
  Wire.write((uint8_t *)&transmit, structSize+1); 
  //transmit the structure over i2c....the +1 is the message lenth + 1 byte to indentify the target text box
  Wire.endTransmission(); 
  
}
