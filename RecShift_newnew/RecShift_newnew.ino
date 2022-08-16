#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int len = 8; //lentgh of each data bit
int detectKey[4] = {1,0,1,0}; //key to detect data
int dataLinePin = 8; //Arduino pin that receives data
int delDet[10] = {90 , 100 , 100 , 100 , 100 , 100 , 100 , 100 , 100 , 105};
int del = 100; //delay time
int dataRowsDec = 10; //same but in decimal

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.print("LIFI  Technology");
  lcd.setCursor(0, 1);
  lcd.print(" DATAs ARE SAFE ");
  pinMode (dataLinePin, INPUT);
}

void loop()
{
x:
int a[8] = {0}; //to hold data bits
int letOrNum; //to set the data is Number or Letter
int pre; //to set the pre data arrayes for Numbers and Letters
String fullId = ""; //to hold the full ID data
if (!digitalRead(dataLinePin) == detectKey[0]){ //detecting start key of data , arg 0
  delay(delDet[0]);
  if(!digitalRead(dataLinePin) == detectKey[1]){  //detecting start key of data , arg 1
    delay(delDet[1]);
    if(!digitalRead(dataLinePin) == detectKey[2]){  //detecting start key of data , arg 2
      delay(delDet[2]);
      if(!digitalRead(dataLinePin) == detectKey[3]){  //detecting start key of data , arg 3
        delay(delDet[3]);
        for( int j = 0 ; j < dataRowsDec; j++ ){  //receiving data in bits step by step
          double id = 0;
          Serial.print(j);
          Serial.print(" : ");
          letOrNum = !digitalRead(dataLinePin); //define that data is number or letter
          delay(del);
          if ( letOrNum == 0 ){ //data bit is number so we add the pre bits of ASCII code
           pre = 4;
           a[0] = 0;
           a[1] = 0;
           a[2] = 1;
           a[3] = 1;
           Serial.print("Number :  ");
          }
          else{ //data bit is letter so we add the pre bits of ASCII code
           pre = 3;
           a[0] = 0;
           a[1] = 1;
           a[2] = 1;
           Serial.print("Letter : ");
          }
          delay(del);
          for(int i = pre ; i < len ; i++){ //receiving and adding the main part of ASCII code
            a[i] = !digitalRead(dataLinePin);
            Serial.print(a[i]);
            delay(del);
           }
          for( int i = 0 ; i < len ; i++){  //converting binary ASCII to decimal ASCII
            if(a[i]==1)
              id += pow(2, (7-i));
          }
          Serial.print(" : ");
          int idChar = id+1;  //decoding ASCII
          for ( int i = 0 ; i < 8 ; i++)
            Serial.print(a[i]);
          Serial.print(" : ");
          if( idChar < 100 )
            Serial.print(" ");
          Serial.print(idChar);
          Serial.print(" -> ASCII : ");
          Serial.print((char)idChar);
          Serial.println();
          fullId += (char)idChar;
        }
      Serial.print("\t \t *-*-*-*-*-*-*-*-*-* \t \t full ID is : "); 
      Serial.println(fullId);
      //Serial.println("Wlcome Dr. Jafari");
      lcd.clear();
      lcd.print("  YOUR ID IS :  ");
      lcd.setCursor(0, 1);
      lcd.print("   " + fullId);
      delay(5000);
      /*
      lcd.clear();
      //lcd.print("welcome DrJafari");
      lcd.setCursor(0, 1);
      //lcd.print("  Arduino.Farsi ");
      delay(2000);
      */
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
