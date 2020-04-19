#include <Adafruit_NeoPixel.h>
#define PIN      6
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Source: http://www.wildcircuits.com/2013/03/optical-mouse-hacking.html
// include the SPI library: 

//Note:  MOSI and MISO connected to eachother!

#include <SPI.h> 
// setup pins 
int nReset = 2; //12 (Changed to 9 because using Arduino Nano)
int nCS = 3; 
void setup(){ 
  //set pin I/O direction 
  pixels.begin();
  pixels.setBrightness(255);
  pixels.clear();
  pinMode (nReset, OUTPUT); 
  pinMode (nCS, OUTPUT); 
  //put the device in reset not chip selected 
  digitalWrite(nReset,LOW); 
  digitalWrite(nCS,HIGH); 
  //initialize SPI 
  SPI.begin(); 
  SPI.setDataMode(SPI_MODE3); 
  //start a serial port for debugging 
  Serial.begin(115200); 
  delay(1000); 
  Serial.println("startup complete"); 
} 
void loop()
{ 
  //enable ADNS 
  digitalWrite(nReset,HIGH); 
  pixel_grab(); 
  delay(150);
}
void ADNS_write(unsigned int address, unsigned int data){ 
  // take the CS pin low to select the chip: 
  digitalWrite(nCS,LOW); 
  //  send in the address and value via SPI: 
  SPI.transfer(address); 
  SPI.transfer(data); 
  // take the SS pin high to de-select the chip: 
  digitalWrite(nCS,HIGH);  
}
unsigned int ADNS_read(unsigned int address){ 
  unsigned int data; 
  // take the CS pin low to select the chip: 
  digitalWrite(nCS,LOW); 
  //  send in the address and value via SPI: 
  SPI.transfer(address); 
  pinMode(MOSI, INPUT); 
  data = SPI.transfer(0x00); 
  pinMode(MOSI, OUTPUT); 
  // take the SS pin high to de-select the chip: 
  digitalWrite(nCS,HIGH);  
  return(data); 
} 

void pixel_grab(){ 
  //address = 0x0b 
  int xcount=0; 
  int count=0; 
   
  //reset the pixel grab counter 
  ADNS_write(0x0B,0x00);
  Serial.println("");   
  for (count=0;count < 225; count++)
  { 
    if (count%15 == 14)
    { 
      uint8_t data = ADNS_read(0x0B);
      if(data  & 0x80)
      {
        Serial.println(String(data - 128));
      }
      else
      {
        count--;
      }
    } 
    else
    { 
      uint8_t data = ADNS_read(0x0B);
      if(data  & 0x80 )
      {
        Serial.print(String(data - 128) + ",");
      }
      else
      {
        count--;
      }
    } 
  } 
  Serial.println(""); 
} 
