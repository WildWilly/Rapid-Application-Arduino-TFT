void DrawScreen()
  {
    uint8_t Data;
    uint16_t indx=0;
    uint16_t tmp;
    uint8_t ObjTest=0;
    
  
    while(ObjTest==0)
        {
         Data=EEPROM.read(indx); 
         //Serial.println(Data);
         switch (Data)
          {
          case 1://screen properties
            {
             EEPROM.get(index,Screen);
             tft.setRotation(Screen.rotation);
             tft.fillScreen(Screen.backColor);//get the colour
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
            tft.setTextColor(txtObj.fontColor);
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
                ButtonPos[buttCount]=indx;
                buttCount++;
               EEPROM.get(indx,butt);
              
             
                    tft.fillRect(butt.x,butt.y,butt.w,butt.h,butt.backColor);//draw box first 
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
                if(Data==4)//Just register Text box objects
                {
                textBoxPos[TextBoxCount]=indx;
                //Serial.println(textBoxPos[TextBoxCount]);
                TextBoxCount++;
                }
                if(txtBox.BorderStyle==1)//1= border 0= no border
                {
                
                tft.drawRect(txtBox.x,txtBox.y,txtBox.w,txtBox.h,txtBox.BorderColor);//draw box first 
                }
                
                tft.fillRect(txtBox.x+2,txtBox.y+2,txtBox.w-4,txtBox.h-4,txtBox.backColor);
                
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
