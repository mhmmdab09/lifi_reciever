#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int len = 8; //lentgh of each data bit
int a[8] = {0}; //to hold data bits
int preData = 0;
int data = 0;
int detectkey[4] = {1,0,1,0}; //key to detect data
int datalinepin = 8; //Arduino pin that receives data
int del = 200; //delay time

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.write("LIFI  Technology");
  lcd.setCursor(0, 1);
  lcd.write(" DATAs ARE SAFE ");
  pinMode (datalinepin, INPUT);
}

void loop()
{
  int n = 0;
  int tim = 0;
  int datarowsbin[8] = {0}; //to hold number of characters in binary
  double datarowsdec = 0; //same but in decimal
    while(!digitalRead(datalinepin) != preData){
      data = !digitalRead(datalinepin);
      tim+=100;
      delay(100);
    }
    n = tim / del;
    for(int i = 0 ; i <= n ; i ++){
      a[i] = data;
      Serial.print(a[i]);
    }
    preData = data;
    Serial.println();
    
}
