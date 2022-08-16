char a=0;
void setup()
{
  Serial.begin(300);

}


void loop()
{
  if (Serial.available()>0){
    a=Serial.read();
    Serial.println(a);
    delay(10);
}}
