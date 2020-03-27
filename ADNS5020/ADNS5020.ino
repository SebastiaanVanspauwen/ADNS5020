// Source: http://www.wildcircuits.com/2013/03/optical-mouse-hacking.html
// include the SPI library: 
#include <SPI.h> 
// setup pins 
int nReset = 2; //12 (Changed to 9 because using Arduino Nano)
int nCS = 3; 
void setup(){ 
  //set pin I/O direction 
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
  //startup time 
  delay(250); 
  pixel_grab(); 
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
  for (count=0;count < 225; count++){ 
    if (count%15 == 14){ 
      Serial.println(String(ADNS_read(0x0B))); 
    } 
    else{ 
      Serial.print(String(ADNS_read(0x0B)) + ","); 
    } 
  } 
  Serial.println(""); 
} 
