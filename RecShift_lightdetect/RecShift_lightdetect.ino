#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define dataLinePin A3 //Arduino pin that receives data
#define envLightPin A2 //Arduino pin that detect the luxe of evnirement

int len = 8; //lentgh of each data bit
int detectKey[4] = {1,0,1,0}; //key to detect data
int delDet[4] = {90 , 100 , 100 , 105}; //detect code delay
int del = 100; //delay time
int dataRowsDec = 4; //number of datas
int lux;
int a2d (int data , int light){
  if(data > light + 50)
    return 1;
  else
    return 0;
}

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
if (a2d(analogRead(dataLinePin) , lux) == detectKey[0]){                //detecting start key of data , arg 0
  delay(delDet[0]);
  if(a2d(analogRead(dataLinePin) , lux) == detectKey[1]){               //detecting start key of data , arg 1
    delay(delDet[1]);
    if(a2d(analogRead(dataLinePin) , lux) == detectKey[2]){             //detecting start key of data , arg 2
      delay(delDet[2]);
      if(a2d(analogRead(dataLinePin) , lux) == detectKey[3]){           //detecting start key of data , arg 3
        delay(delDet[3]);
        for( int j = 0 ; j < dataRowsDec; j++ ){
          double id = 0;
          Serial.print(j);
          Serial.print(" : ");
          letOrNum = a2d(analogRead(dataLinePin) , lux);
          delay(del);
          if ( letOrNum == 0 ){
           pre = 4;
           a[0] = 0;
           a[1] = 0;
           a[2] = 1;
           a[3] = 1;
           Serial.print("Number :  ");
          }
          else{
           pre = 3;
           a[0] = 0;
           a[1] = 1;
           a[2] = 1;
           Serial.print("Letter : ");
          }
          delay(del);
          for(int i = pre ; i < len ; i++){
            a[i] = a2d(analogRead(dataLinePin) , lux);
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
          Serial.print(" -> ASCII : ");
          Serial.print((char)idChar);
          Serial.println();
          fullId += (char)idChar;
        }
      Serial.print("\t \t *-*-*-*-*-*-*-*-*-* \t \t full ID is : "); 
      Serial.println(fullId);
      lcd.clear();
      lcd.print("  YOUR ID IS :  ");
      lcd.setCursor(0, 1);
      lcd.print("      " + fullId);
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
if(analogRead(envLightPin) > lux + 10 || analogRead(envLightPin) < lux - 50)
  lux = analogRead(envLightPin);
}
