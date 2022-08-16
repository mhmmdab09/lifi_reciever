#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int lengh = 8; //lentgh of each data bit
int ascii_array[8] = {0}; //to hold data bits
int prev_data = 0;
int current_data = 0;
int start_key[4] = {1,0,1,0}; //key to detect data
int datalinepin = 8; //Arduino pin that receives data
int res_delay = 200; //delay time

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

void loop() {
  int sum_del = 0;
  String serial = "";
  //current_data = !digitalRead(datalinepin);
  while(prev_data != !digitalRead(datalinepin)){
    Serial.print("changed\n");
    Serial.print(current_data);

    serial+= current_data;
    delay(res_delay);
    sum_del += res_delay;
  }
  prev_data = current_data;
  Serial.print(serial + "\n");
  //delay(res_delay);
}
