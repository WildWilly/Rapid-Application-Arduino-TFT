
void receiveEvent(int howMany) 
{
  byte Data;
  Data=Wire.read();//read 1 byte. This will indicate what object is being called
  for(byte tb=0; tb< TextBoxCount;tb++)
    {
      if (EEPROM.read(textBoxPos[tb]+1)==Data)
        {
        EEPROM.get(textBoxPos[tb],txtBox);
        EEPROM.get(textBoxPos[tb]+15,txtObj);//text portion
        tft.setTextSize(txtObj.fontSize);
        tft.setTextColor(txtObj.fontColor);
        tft.fillRect(txtBox.x+2,txtBox.y+2,txtBox.w-4,txtBox.h-4,txtBox.backColor);//erase former text 
        tft.setCursor(txtObj.x,txtObj.y);
        while(Wire.available()) 
          {
          char txtData=Wire.read();
          tft.print(txtData);
          }
        }
    }

}

//*************************************************************************************
void requestEvent()
{
   //The master unit will poll the slave looking to see if a button is pushed.
  Wire.write(SelectedIndex);
//lcd.clear();
//lcd.print(SelectedIndex);
}
//**************************************************************************************
void touchDetect()
{
   uint16_t xpos, ypos;  //screen coordinates
 // Calibrated for a 400 X 240 screen in #0 landscape mode

  tp = ts.getPoint();   //tp.x, tp.y are ADC values
 static uint16_t Pressure;
 static uint16_t DelayCount;
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
 
  if (millis()-TimeElapsed>25 && Flag==1)
  {
   // Serial.print("button up");Serial.println(TimeElapsed);
     // TimeElapsed=0;
     Flag=0;
     buttonClicked=0;
     animateButton(false);
     SelectedIndex=0;
  } 
test=tp.z;
if (Screen.rotation==0)
{
 xpos = map(tp.x, TS_LEFT, TS_RT, 0,tft.width());
 ypos = map(tp.y, TS_TOP, TS_BOT, 0,tft.height());
}
else
{
 xpos = map(tp.y, TS_TOP,TS_BOT, 0,tft.width());
 ypos = map(tp.x, TS_RT, TS_LEFT, 0,tft.height());
 //Serial.println(tft.width)
}

    if (test > MINPRESSURE && test < MAXPRESSURE && buttonClicked==0)
    {
 
    for(byte tmpCount=0;tmpCount<buttCount;tmpCount++)
     {
       EEPROM.get(ButtonPos[tmpCount],butt);
     
       if (xpos>butt.x&&xpos<=(butt.x+butt.w)&&ypos>=butt.y&&ypos<(butt.y+butt.h))
        {
       // Serial.println("detect");
        SelectedIndex=EEPROM.read(ButtonPos[tmpCount]+1);
    
          animateButton(true);
          buttonClicked=1;
        
         break;
         }
     
     }
     
    }

   if(buttonClicked==1 && xpos>butt.x&&xpos<=(butt.x+butt.w)&&ypos>=butt.y&&ypos<(butt.y+butt.h))
 {
  
      SelectedIndex=0;
      TimeElapsed=millis();
      Flag=1;
      delay(400);
 }


}
