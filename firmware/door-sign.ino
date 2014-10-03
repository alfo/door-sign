#include "application.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C   *lcd;
String eventName = "";
String eventLocation = "";
String eventCal = "";
String titleText = "";

void setup()
{
    lcd = new LiquidCrystal_I2C(0x27, 20, 4);
    lcd->init();
    lcd->backlight();
    lcd->clear();

    // Placeholder text before we recieve first update
    lcd->setCursor(0,0);
    lcd->print("Alex is at:");

    // Register the Spark cloud functions
    Spark.function("update", update);
    Spark.function("backlight", backlight);
}

// Don't need anything here
void loop() {

}

// Backlight on/off function
int backlight(String args) {
  if (args == "on") {

    // Set the backlight of the LCD to on
    lcd->backlight();

    // Put the Spark's inbuilt LED to 100%
    RGB.brightness(255);
  } else if (args == "off") {

    // Set the backlight of the LCD to off
    lcd->noBacklight();

    // Dim the inbuild LED
    RGB.brightness(25);
  }

  return 1;
}

// Runs to update the screen
int update(String args) {

    String temp = getValue(args, '|', 0);
    titleText = temp;

    String temp1 = getValue(args, '|', 1);
    eventName = temp1;

    String temp2 = getValue(args, '|', 2);
    eventLocation = temp2;

    String temp3 = getValue(args, '|', 3);
    eventCal = temp3;

    lcd->setCursor(0, 0);
    lcd->print("                    ");
    lcd->setCursor(0, 0);
    lcd->print(titleText);

    lcd->setCursor(0, 1);
    lcd->print("                    ");
    lcd->setCursor(0, 1);
    lcd->print(eventName);

    lcd->setCursor(0, 2);
    lcd->print("                    ");
    lcd->setCursor(0, 2);
    lcd->print(eventLocation);

    lcd->setCursor(0, 3);
    lcd->print("                    ");
    lcd->setCursor(0, 3);
    lcd->print(eventCal);

    return 1;

}

// Helper function to split strings by the "|" seperator
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i = 0; i <= maxIndex && found <= index; i++){
    if(data.charAt(i) == separator || i == maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
