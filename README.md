# Rapid application system for Arduino TFT displays.
Rapidly develop your Aurduino TFT display using using WSIWIG GUI tools 

You know the old story. You look at a pile of examples on how to design a display for your new 3.5 inch TFT shield. First you take an Arduino Uno or what ever ATmega328P  variation you have. Print a box here and some text there. Maybe you figured out how create a routine to detect a button push. What you did find out was that the shield used most of the available ports and all of the memory. Practical use with servo's stepper motors, or sensors becomes a challenge.  The only alternative up to now would have been a Mega or start learning about STM32's 

Here I present a new philosophy on how to program a TFT using a Arduino. At the time of this publishing; the Control-Pannel sketch consumed just 54% of program memory and 30% of dynamic memory. The module is intended to be a I2C slave but my OpenSmart tft shield has made 2 analog ports and two digital ports available for use.

 The system was developed using the Adafruit_GFX.h library so if your display supports the GFX library then tweeking the initialization code should be easy.

Overview:
VBA Excel(2003)is used to create a graphical user interface (GUI )to simulate the TFT screen. 
From the  VBA tool box. Buttons, Labels, and Text boxes are pulled into a frame that represents the screen.
Click “Compile” to save the basic data into a hex file.
Click “Transpose”. The data is automatically added into an “Arduino burn EEPROM template” sketch that is stored within Excel itself.
The template is then automatically saved and launched.
When you run the burn sketch the data is stored in the Uno's EEPROM space. 1024 bytes max. The example uses 387 bytesof EEPROM space.
Load the final CntrlPannel Slave sketch. Data stored in the EEPROM doesn't change even if a new sketch is loaded. 
The size and memory used in this file never changes.
Load the Master sketch on another Arduino to create the I2C slave, master relation.

What do you get :
Labels: 
They are static. Their values can not be changed.
The more words used. The more EEPROM space used.
Text boxes:
They are dynamic.
Numbers or Text can be sent from the I2C master using the Text Box object reference number.
Initial text is stored in the EEPROM.
Buttons:
Buttons are animated. (they appear to move when pressed)
When pressed their object reference number is registered.
 The I2C master will constantly poll looking if a number is registered


