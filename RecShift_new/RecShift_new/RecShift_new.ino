#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int len = 8; //lentgh of each data bit
int detectKey[4] = {1,0,1,0}; //key to detect data
int dataLinePin = 8; //Arduino pin that receives data
int del = 30; //delay time

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.write("LIFI  Technology");
  lcd.setCursor(0, 1);
  lcd.write(" DATAs ARE SAFE ");
  pinMode (dataLinePin, INPUT);
}

void loop()
{
x:
int a[8] = {0}; //to hold data bits
int dataRowsBin[8] = {0}; //to hold number of characters in binary
double dataRowsDec = 4; //same but in decimal
int chOrNum; //to set the data is Number or Character
int pre; //to set the pre data arrayes for Numbers and Characters
String fullId = ""; //to hold the full ID data
if (!digitalRead(dataLinePin) == detectKey[0]){                //detecting start key of data , arg 0
  delay(del);
  if(!digitalRead(dataLinePin) == detectKey[1]){               //detecting start key of data , arg 1
    delay(del);
    if(!digitalRead(dataLinePin) == detectKey[2]){             //detecting start key of data , arg 2
      delay(del);
      if(!digitalRead(dataLinePin) == detectKey[3]){           //detecting start key of data , arg 3
        delay(1.5 * del);
        /*
        Serial.print("size of data : ");
        for(int i = 0 ; i < 8 ; i++){
          delay(del);
          dataRowsBin[i] = !digitalRead(dataLinePin);
          if(dataRowsBin[i]==1)
            dataRowsDec += pow(2, (7-i));
          Serial.print(dataRowsBin[i]);
        }
        Serial.print(" : ");
        Serial.println(dataRowsDec);
        delay(del);
        */
        for( int j = 0 ; j < dataRowsDec; j++ ){
          double id = 0;
          Serial.print(j);
          Serial.print(" : ");
          chOrNum = !digitalRead(dataLinePin);
          delay(del);
          if ( chOrNum == 0 ){
           pre = 4;
           a[0] = 0;
           a[1] = 0;
           a[2] = 1;
           a[3] = 1;
           Serial.print("  Number  :  ");
          }
          else{
           pre = 3;
           a[0] = 0;
           a[1] = 1;
           a[2] = 1;
           Serial.print("Character : ");
          }
          delay(del);
          for(int i = pre ; i < len ; i++){
            a[i] = !digitalRead(dataLinePin);
            Serial.print(a[i]);
            delay(del);
           }
          for( int i = 0 ; i < len ; i++){
            if(a[i]==1)
              id += pow(2, (7-i));
          }
          Serial.print(" : ");
          int idChar = id+1;
          for ( int i = 0 ; i < 8 ; i++)
            Serial.print(a[i]);
          Serial.print(" : ");
          if( idChar < 100 )
            Serial.print(" ");
          Serial.print(idChar);
          Serial.print(" : ");
          Serial.print((char)idChar);
          Serial.println();
          fullId += (char)idChar;
        }
      Serial.print("\t \t *-*-*-*-*-*-*-*-*-* \t \t full ID is : "); 
      Serial.println(fullId);
      lcd.clear();
      lcd.print(fullId);
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
