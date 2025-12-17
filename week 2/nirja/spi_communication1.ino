#include<SPI.h>                                      
#define button 2

bool buttonPressed = false;


void setup (){
  Serial.begin(9600);                                                    
  SPI.begin();                            
  digitalWrite(SS,HIGH);
  attachInterrupt(digitalPinToInterrupt(button), button_in, RISING);
}

void button_in(){
  buttonPressed = true;
}

void loop(){
  if(buttonPressed)
  {
    char c;
    digitalWrite(SS, LOW);  
    for (const char * p = "Button pressed\r"; c = *p; p++)
      SPI.transfer(c);
    digitalWrite(SS, HIGH); 
    buttonPressed = false;
  }//end if(buttonPressed)
}
