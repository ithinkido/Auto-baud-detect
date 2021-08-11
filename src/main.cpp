#include <Arduino.h>
HardwareSerial plotter_serial(2);
const uint16_t serialBauds[] = {19200, 9600, 4800, 2400, 1200, 600, 300, 200, 150, 110, 75}; 
uint8_t serialBaudIndex;

void setup() {
  Serial.begin(9600);
  delay(10);
  String baud_response;
  bool eol = false;
  while (baud_response.length() == 0 && (eol == false )){
    plotter_serial.begin(serialBauds[serialBaudIndex]);  
    plotter_serial.write("IN;OI;");
    baud_response = plotter_serial.readStringUntil('\r'); 
    serialBaudIndex++ ;
    if (serialBaudIndex > sizeof(serialBauds) / sizeof(serialBauds[0])) {
      eol = true;    
    }
  }
  if (eol == true) {
    Serial.println(" Plotter not detected ");
  }
  else{
    plotter_serial.println("IN");
    Serial.print ("Plotter baud rate is : ");
    Serial.println (serialBauds[serialBaudIndex -1]);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}