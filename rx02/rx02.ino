#include<LiquidCrystal.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

int len = 8;
int a[8] = {0};
int detectkey[4] = {1,0,1,0};
int datalinepin = 8;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print(" LIFI Technology");
  lcd.setCursor(0, 1);
  lcd.print(" DATAs ARE SAFE ");
  pinMode (8, INPUT);  
}

void loop()
{
x:
int id = 0;
if (!digitalRead(datalinepin) == detectkey[0]){                //detecting start key of data , arg 0
  delay(10);
  if(!digitalRead(datalinepin) == detectkey[1]){               //detecting start key of data , arg 1
    delay(10);
    if(!digitalRead(datalinepin) == detectkey[2]){             //detecting start key of data , arg 2
      delay(10);
      if(!digitalRead(datalinepin) == detectkey[3]){           //detecting start key of data , arg 3
        delay(10);
        lcd.clear();
        for(int i=0 ; i<len ; i++){                            //replce the data bits to array
          a[i] = !digitalRead(8);
          Serial.print(a[i]);
          delay(10);
        }
      Serial.print (" -> ");
      for (int i=0; i<len; i++){
        id+=(a[i]*(pow(2,((len-1)-i))));
      }
      Serial.print (id);
      Serial.print (" : ");
      switch (id){
        case 1:
          Serial.print("Mohammad Abtahi ");
          Serial.println(" -> Loged In");
          lcd.print("Mohammad Abtahi");
          lcd.setCursor(0, 1);
          lcd.println(" welcome :) ");
          break;
        case 2:
          Serial.print("Ali Loghmanian");
          Serial.println(" -> Loged In");
          lcd.print("Ali Loghmanian");
          lcd.setCursor(0, 1);
          lcd.print(" welcome :) ");
          break;
        case 3:
          Serial.print("Dr. Jafari");
          Serial.println(" -> Loged In");
          lcd.print("Dr. Jafari");
          lcd.setCursor(0, 1);
          lcd.print(" welcome :) ");
          break;
        case 4:
          Serial.print("Mohammad Sharifi");
          Serial.println(" -> Loged In");
          lcd.print("Mohammad Sharifi");
          lcd.setCursor(0, 1);
          lcd.print(" welcome :) ");
          break;
        /*default:
          Serial.println("not found ->  ");
          lcd.print("not found");
          break;*/
      }
      delay(2000);
      lcd.clear();
      lcd.print(" LIFI Technology");
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
