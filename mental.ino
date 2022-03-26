#include <LedControl.h>


#define POWER_PIN  7
#define SIGNAL_PIN A5
//joy
#define joyX A0
#define joyY A1
int xContrant;
int yContrant;
int value = 0; // variable to store the sensor value
//led
int DIN = 12;
int CS =  11;
int CLK = 10;

byte resting[8]=     {0x00,0x66,0x66,0x00,0x00,0x3C,0x00,0x00,};
byte lookLeft[8] = {0x00,0x33,0x33,0x00,0x10,0x1E,0x00,0x00,};
byte lookRight[8] = {0x00,0xCC,0xCC,0x00,0x08,0x78,0x00,0x00,};
byte Heart[8]=   {0x00,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x00,};

LedControl lc=LedControl(DIN,CLK,CS,0);

void setup() {
  //water
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  //joy
  xContrant = analogRead(joyX);
  yContrant = analogRead(joyY);
  //led
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,5);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop() {
  xContrant = analogRead(joyX);
  yContrant = analogRead(joyY);
  //water
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int istouch;
  int headpat;
  
  if(value > 2){
    istouch = 1;
    if(istouch == 1){
        Serial.print("I love holding hands\n");
            printByte(Heart);
            delay(30);


    }

    //do something
  }else{
       lc.clearDisplay(0);
       delay(15);
      if(istouch == 0 &&(xValue <= xContrant-5 || xValue >= xContrant+5 || yValue <= yContrant-5 || yValue >= yContrant+5  )){
         // Serial.println("headpats");
           printIdle();
    istouch = 0;
          //here we do something
    
  }

  }
 





}
void headpat(){
  
}
void printIdle()
{
 
  
  printByte(resting);
  delay(500);
 lc.clearDisplay(0);

  
}


void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}


