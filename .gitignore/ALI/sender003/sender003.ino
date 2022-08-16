int det[4]={1,0,1,0};
int num[8]={0};
int number;
void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 HERE:
 Serial.begin(9600);
  if (Serial.available())
    {
      number= Serial.parseInt();
         //Serial.println(number,BIN);
                  for (int j=0 ; j<4 ; j++)
                           {
                              if (det[j]==0)
                              {
                               digitalWrite (8,LOW);
                               delay(10);
                              }
                              else
                              {
                               digitalWrite (8,HIGH);
                               delay(10);
                              }
                           }
          
               delay(10);
         for (int i=7 ; i>=0 ; i--)
         { 
            num[i]=number%2;
            number/=2; 
         }
                
      for (int k=0 ; k<8 ; k++)
          {
            //Serial.print(Serial.read());
            if (num[k]==0)
              {
               digitalWrite (8,LOW);
               delay(10);
              }
            else
              {
               digitalWrite (8,HIGH);
               delay(10);
              }
          }
                    Serial.println(number,BIN);
                    digitalWrite(8,LOW);
                    Serial.end();

          delay(10);
   goto HERE; }
 else
    delay(10);
   goto HERE;
   
}
