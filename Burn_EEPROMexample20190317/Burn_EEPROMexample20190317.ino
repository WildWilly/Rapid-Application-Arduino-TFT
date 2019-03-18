//This file was automatically created by TFTBurnerDemo2019_mm_dd.xls
#include <EEPROM.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>//this library is specific to the OpenSmart tft dispaly

MCUFRIEND_kbv tft;
//Data will be added to this point
const byte tft_Data[]{1, 1, 1, 205, 139, 90, 4, 2, 24, 0, 11, 0, 88, 1, 26, 0, 12, 248, 83, 0, 0, 0, 0, 2, 0, 0, 0, 18, 0, 84, 104, 
105, 115, 32, 105, 115, 32, 97, 32, 116, 101, 120, 116, 32, 98, 111, 120, 4, 3, 245, 0, 45, 0, 141, 0, 28, 0, 205, 139, 90, 1, 
255, 255, 0, 2, 0, 0, 0, 10, 0, 84, 101, 120, 116, 66, 111, 120, 49, 50, 51, 5, 4, 131, 0, 104, 0, 150, 0, 16, 0, 205, 
139, 90, 1, 0, 0, 0, 1, 0, 0, 0, 21, 0, 76, 97, 98, 101, 108, 115, 32, 97, 114, 101, 32, 101, 109, 98, 101, 100, 101, 100, 
46, 32, 32, 5, 5, 98, 0, 132, 0, 218, 0, 16, 0, 243, 238, 139, 1, 0, 0, 0, 1, 255, 53, 53, 28, 0, 108, 101, 116, 116, 
101, 114, 115, 32, 115, 117, 99, 107, 32, 117, 112, 32, 69, 69, 80, 82, 79, 77, 32, 115, 112, 97, 99, 101, 5, 6, 11, 0, 81, 0, 
13, 1, 15, 0, 228, 225, 232, 0, 0, 0, 0, 1, 0, 64, 128, 34, 0, 76, 65, 66, 69, 76, 32, 78, 79, 32, 66, 79, 82, 68, 
69, 82, 32, 67, 79, 76, 79, 82, 69, 68, 32, 66, 65, 67, 75, 103, 114, 111, 117, 110, 100, 3, 7, 49, 0, 174, 0, 94, 0, 34, 
0, 210, 45, 165, 1, 1, 0, 0, 0, 6, 0, 84, 101, 115, 116, 32, 49, 3, 8, 201, 0, 177, 0, 146, 0, 34, 0, 240, 240, 240, 
1, 1, 0, 0, 0, 14, 0, 67, 111, 109, 109, 97, 110, 100, 66, 117, 116, 116, 111, 110, 50, 5, 9, 25, 0, 50, 0, 160, 0, 21, 
0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 255, 0, 6, 0, 76, 97, 98, 101, 108, 49, 0};

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define WHITE   0xFFFF

//int TotalRead=0;
int CurrentCount=0;
int eeAddress=0;
int tft_Data_Index=0;
uint8_t index=0;
bool BeginFlag=false;

uint16_t TS_LEFT = 868;
uint16_t TS_RT  = 169;
uint16_t TS_TOP = 942;
uint16_t TS_BOT = 110;



struct INITSCREEN //5 bytes
       {
        uint8_t type;
        uint8_t index;
        uint8_t rotation;
        uint16_t BackColor;
       };

struct BUTTON //13 bytes
      {
        uint8_t type;
        uint8_t index;
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
        uint16_t BackColor;
        bool fill;
      
      };
struct TEXTOJECT //10 bytes
      {
        uint8_t type;
        uint8_t index;
        uint16_t x;
        uint16_t y;
        uint8_t fontSize;
        uint16_t txtcolor;
        uint8_t StrngLen;
       
      };
struct TEXTBOX //18 bytes
      {
        uint8_t type;//1 byte
        uint8_t index;//1 byte
        uint16_t x;//2 byte
        uint16_t y;//2 byte
        uint16_t w;//2 byte
        uint16_t h;//2 byte
        uint16_t BackColor;//2 byte
        uint8_t BorderStyle;//1 byte
        uint16_t BorderColor;//2 byte
      };
//declare structure objects
static BUTTON butt={};
static TEXTOJECT txtObj={};  
static INITSCREEN Screen={};
static TEXTBOX txtBox={};
//**********************************************************************************************

void setup()
 {
//  Wire.begin(NodeAddressSlave);
  Serial.begin(9600);
  tft.reset();

  uint16_t identifier = tft.readID();
 uint16_t tmploop=0;
  tft.begin(identifier);
  tft.fillScreen(BLACK);
 tft.setTextColor(WHITE);
 tft.setTextSize(3);
 tft.println("Cleaning EEPROM:");
 delay(1000);
 for(tmploop=0;tmploop<1024;tmploop++)
 {
 EEPROM.update(tmploop,255);// write 255 to eeprom to set it back to default
   tft.print(".");
//Serial.println(EEPROM.read(tmploop)); 
 }
//for(;;){}
 
 }

void loop()
{ 
  tft.fillScreen(BLACK);
           delay(100);  
          uint8_t objType=getBytes(1);
          tft.setCursor(0,10);
         tft.print("Obj :");tft.print(objType);
          delay(100);
          switch (objType) {
              case 1://InitialScreen
                    {
                      
                      Screen.type=objType;
                      Screen.index=getBytes(1);
                      Screen.rotation=getBytes(1);
                      Screen.BackColor=RGB565();
                     
                      EEPROM.put(eeAddress,Screen);
                      
                      eeAddress=eeAddress+5;
            
                    break;
                    }
               
             
              case 2: //text object 
                    {
                     
                      txtObj.type=objType;//1 byte
                      txtObj.index=getBytes(1);//1 byte
                       
                      txtObj.x=getBytes(2);//2 byte
                      txtObj.y=getBytes(2);//2 byte
                      txtObj.fontSize=getBytes(1);//1 byte
                      txtObj.txtcolor=RGB565();//2 byte
                      txtObj.StrngLen=getBytes(1);//1 byte
                 
                      EEPROM.put(eeAddress, txtObj);
                      eeAddress=eeAddress+10;
                      //TotalWrite=TotalWrite+10;
                      byte discardByte=getBytes(1);//datafile stores text length as 2 bytes. we just need 1
                     ProcessText();
                     
                      break;
                     }
               
              case 3:    //Button
                    {
                    
                      butt.type=objType;//1 byte
                      butt.index=getBytes(1);//1 byte
                      butt.x=getBytes(2);//2 bytes
                      butt.y=getBytes(2);//2 bytes 
                      butt.w=getBytes(2); //2 bytes
                      butt.h=getBytes(2);//2 bytes
                      butt.BackColor=RGB565();//2 bytes
                      butt.fill=getBytes(1);//1 byte
                       
                    EEPROM.put(eeAddress,butt);
                      eeAddress=eeAddress+13;
                      
              
          //*******************************************************************************************            
                      
                      txtObj.type=2;//1 byte
                      txtObj.index=butt.index; //the button and text will share the same index //1 byte
                      txtObj.fontSize=getBytes(1);//1 byte
                      txtObj.txtcolor=RGB565();//2 byte
                      txtObj.StrngLen=getBytes(1);//1 byte
                      byte discardByte=getBytes(1);
                      uint16_t CenterX=butt.x;
                      uint16_t CenterY=butt.y;
                   
                      //center text inside box
                      CenterCalc(CenterX,CenterY,butt.w,butt.h, txtObj.StrngLen,txtObj.fontSize);
                      txtObj.x=CenterX;//multi byte read function //2 byte
                      txtObj.y=CenterY;//2 byte
          
                     //write text portion of buttorn
                     EEPROM.put(eeAddress, txtObj);
                      eeAddress=eeAddress+10;
                      //TotalWrite=TotalWrite+10;
                     ProcessText();
          
                     break;
                    }
                case 4:case 5://text box
                    {
                      txtBox.type=objType;//1 byte
                      txtBox.index=getBytes(1);//1 byte
                      txtBox.x=getBytes(2);//2 bytes
                      txtBox.y=getBytes(2);//2 bytes 
                      txtBox.w=getBytes(2); //2 bytes
                      txtBox.h=getBytes(2);//2 bytes
                      
                      txtBox.BackColor=RGB565();//2 bytes
                      txtBox.BorderStyle=getBytes(1);//1 byte
                     
                      txtBox.BorderColor=RGB565();//2 bytes
                      EEPROM.put(eeAddress,txtBox);
                      eeAddress=eeAddress+15;
                       //*******************************************************************************************            
                      
                      txtObj.type=2;//1 byte
                      txtObj.index=txtBox.index; //the button and text will share the same index //1 byte
                      txtObj.fontSize=getBytes(1);//1 byte
                      txtObj.txtcolor=RGB565();//2 byte
                      txtObj.StrngLen=getBytes(1);//1 byte
                      byte discardByte=getBytes(1);//unwanted byte automatically from the binary file
                      
                       uint16_t CenterX=txtBox.x;
                      uint16_t CenterY=txtBox.y;
                   
                      //center text inside box
                      CenterCalc(CenterX,CenterY,txtBox.w,txtBox.h, txtObj.StrngLen,txtObj.fontSize);
                      
                      txtObj.x=txtBox.x+4;
                      txtObj.y=CenterY;
          
                      //write text portion of textbox or label
                       EEPROM.put(eeAddress, txtObj);
                      eeAddress=eeAddress+10;
                      ProcessText();
          
                      break;
                      
                    }
            }
  
}
//**************************************************************************************************************************************************************
uint16_t getBytes(uint8_t bytesExpected)
{
 uint16_t  lngValue;
 uint16_t nodePayload[2];
 
 for (uint8_t readloop=0; readloop<=bytesExpected-1; readloop++)
     {
       nodePayload[readloop] = tft_Data[tft_Data_Index];
 
       tft_Data_Index++;
       if (tft_Data_Index==sizeof(tft_Data))
       {
        DrawScreen();
        delay (3000);
        
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.setCursor(0,0);
        tft.print("Write volume is ");
        tft.print(eeAddress);
        tft.println(" bytes");
        if (eeAddress>1023)
          {
           tft.fillScreen(BLACK);
           tft.setCursor(0,10);
           tft.print("file size");
           tft.setCursor(0,20);
           tft.print(eeAddress);
           tft.setCursor(0,30);
           tft.print("Too Big");
          };
        delay (5000);
        DrawScreen();
        for(;;){}
       }
     }
     
     lngValue= (uint16_t) (nodePayload[1] << 8) | nodePayload[0];  //rebuild long value

 return lngValue;
    
}
//*************************************************************************************************************************************************************

///Thanks to the creator of this site for the algorithm to convert RGB888 to RGB565
//http://www.barth-dev.de/online/rgb565-color-picker/

uint16_t RGB565()
{
 
  uint8_t RED=getBytes(1);
  uint8_t GREEN=getBytes(1);
  uint8_t BLUE=getBytes(1);
 uint16_t RGB = (((RED & 0xf8)<<8) + ((GREEN & 0xfc)<<3)+(BLUE>>3));
  return RGB;
 
}


//*****************************************************************************************
void CenterCalc(uint16_t &txtX,uint16_t &txtY,uint16_t w,uint16_t h, uint8_t stringlength,uint8_t fontSize)
 {  
   //uint16_t pData[2];
   uint8_t FontW;
   uint8_t FontH;
   uint8_t FontSpace;
  
    switch (fontSize)
        {
          case 1:
            FontW=5;
            FontH=7;
            FontSpace=1;
            break;
          case 2:
            FontW=10;
            FontH=14;
            FontSpace=1;
            break;
          case 3:
            FontW=15;//15
            FontH=21;
            FontSpace=3;
            break;
          case 4:
            FontW=20;
            FontH=28;
            FontSpace=4;
            break;
          case 5:
            FontW=25;
            FontH=35;
            FontSpace=5;
            break;
        }
   

uint8_t tmplen=stringlength-1;
  uint8_t TextWidth=(FontW*stringlength)+(FontSpace*tmplen);


  uint16_t PosX=(w-TextWidth)/2;//screen 400 pixels wide
 if (TextWidth>w)PosX=0;

  txtX = txtX+PosX;
  uint8_t PosY=(h-FontH)/2;
  txtY = txtY+PosY;
 
 }
void ProcessText()
{
  byte testDat=0;
 
            for(testDat=0;testDat<txtObj.StrngLen;testDat++)//
            
            {
             char Data =getBytes(1);//str[iteration]
    
          EEPROM.put(eeAddress,Data );
            eeAddress++;
           
            }
    

}
void DrawScreen()
  {
    uint8_t Data;
    uint16_t indx=0;
    uint16_t tmp;
    uint8_t ObjTest=0;
    uint8_t buttCount=0;
    uint8_t TextBoxCount=0;
  
    while(ObjTest==0)
        {
         Data=EEPROM.read(indx); 
         //Serial.println(Data);
         switch (Data)
          {
            case 1://screen properties
              {
               EEPROM.get(index,Screen);
               //Screen.rotation=1;
               tft.setRotation(Screen.rotation);
                switch (Screen.rotation)//adjust touch screen orientation
                {      // adjust for different aspects
                    case 0:   break;        //no change,  calibrated for PORTRAIT
                    case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
                    //case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
                   // case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
                }
             
             tft.fillScreen(Screen.BackColor);//get the colour
            delay(250);
               if(EEPROM.read(indx+6)!=Screen.index+1)
               {
                ObjTest=1;// if the indexes are not sequential then end.
               }
             
               indx=indx+5;
              
               break; 
              }
            case 2://text object
              {
            
              EEPROM.get(indx,txtObj); 
              tft.setCursor(txtObj.x,txtObj.y);
              tft.setTextColor(txtObj.txtcolor);
              tft.setTextSize(txtObj.fontSize);
              indx=indx+10;
               
                for (byte counter=0; counter<txtObj.StrngLen; counter++)
                  {
                     char Character=EEPROM.read(indx+counter);
                    tft.print(Character);
                  }
            
               if(EEPROM.read(indx+txtObj.StrngLen+1)!=txtObj.index+1)
               {
                ObjTest=1;// if the indexes are not sequential then end.
             
               }
               indx=indx+txtObj.StrngLen;
               break; 
              }       
         case 3://button.. text portion is sent via the text routine
              {
                //ButtonPos[buttCount]=indx;
                //buttCount++;
               EEPROM.get(indx,butt);
              
             
                    tft.fillRect(butt.x,butt.y,butt.w,butt.h,butt.BackColor);//draw box first 
                   //draw 3d lines
                    animateButton(false);
                 
                //Test to end not required here as Text object must follow.

               indx=indx+13;
               
               break; 
              }
        
       
        case 4:case 5:// Text Box and label
              {
               //Serial.println("Text box selected");
                EEPROM.get(indx,txtBox);
               // textBoxPos[TextBoxCount]=indx+1;
               // TextBoxCount++;
               //Serial.println("border style");
                //Serial.println(txtBox.BorderStyle);
                if(txtBox.BorderStyle==1)//1= border 0= no border
                {
                
                  tft.drawRect(txtBox.x,txtBox.y,txtBox.w,txtBox.h,txtBox.BorderColor);//draw box first 
                }
               
                tft.fillRect(txtBox.x+2,txtBox.y+2,txtBox.w-4,txtBox.h-4,txtBox.BackColor);
             
                indx=indx+15;//text to automatically follow
               break; 
              }
          default:        {break;}
        }   
        
        }
}
//***************************************************************************************************
void animateButton(bool Down)
{
  uint16_t SideOne;
  uint16_t SideTwo;
  if (Down==false)
  {
    SideOne=BLACK;
    SideTwo=WHITE;
  }
  else
  {
    SideOne=WHITE;
    SideTwo=BLACK;
  }
  tft.drawLine(butt.x,butt.y+butt.h,butt.x+butt.w, butt.y+butt.h, SideOne);//create shadow
  tft.drawLine(butt.x+butt.w,butt.y, butt.x+butt.w, butt.y+butt.h, SideOne);
        
  tft.drawLine(butt.x,butt.y, butt.x, butt.y+butt.h,SideTwo);
  tft.drawLine(butt.x,butt.y-1, butt.x+butt.w, butt.y-1, SideTwo);
}
