#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int len = 8; //lentgh of each data bit
int a[8] = {0}; //to hold data bits
int detectkey[4] = {1,0,1,0}; //key to detect data
int datalinepin = 8; //Arduino pin that receives data
int del = 100; //delay time

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
x:
String idchar = "";
int datarowsbin[8] = {0}; //to hold number of characters in binary
double datarowsdec = 0; //same but in decimal
if (!digitalRead(datalinepin) == detectkey[0]){                //detecting start key of data , arg 0
  delay(del);
  if(!digitalRead(datalinepin) == detectkey[1]){               //detecting start key of data , arg 1
    delay(del);
    if(!digitalRead(datalinepin) == detectkey[2]){             //detecting start key of data , arg 2
      delay(del);
      if(!digitalRead(datalinepin) == detectkey[3]){           //detecting start key of data , arg 3
        delay(del);
        delay(del/2);
        Serial.print("size of data : ");
        for(int i=0 ; i<8 ; i++){
          datarowsbin[i] = !digitalRead(datalinepin);
          if(datarowsbin[i]==1)
            datarowsdec += pow(2, (7-i));
          Serial.print(datarowsbin[i]);
          delay(del);
        }
        Serial.print(" : ");
        Serial.println(datarowsdec);
        lcd.clear();
        delay(del);
        double id = 0;
        for( int j=0 ; j<datarowsdec; j++ ){
            Serial.print(j);
            Serial.print(" : ");
            for(int i=0 ; i<len ; i++){
              a[i] = !digitalRead(datalinepin);
              if(a[i]==1)
                id += pow(2, (7-i));
              Serial.print(a[i]);
              delay(del);
            }
          Serial.print(" : ");
          Serial.println();
        }
      for( int j=0 ; j<datarowsdec; j++ ){
        idchar += ((char)(id+1));
      }
      Serial.println (idchar);
      //lcd.write((char)idchar);
      Serial.println();
      delay(3500);
      lcd.clear();
      lcd.print("LIFI  Technology");
      lcd.setCursor(0, 1);
      lcd.print(" DATAs ARE SAFE ");
      }
      else
      goto x; 
    }
    else
    goto x; 
  }
  else
  goto x; 
}
else
goto x;

}
