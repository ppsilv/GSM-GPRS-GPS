//We use NO configuration for 5V relay module.So, when an input pin is LOW the relay is OFF,
//if it is HIGH - the relay is ON, the circuit will be complete, and a light or sound switched on.

#include <SoftwareSerial.h> // Library for using software serial communication
SoftwareSerial SIM900(7, 8); // Digital pins 7 and 8 of Arduino Uno board are used as used as software serial pins

String outgoingData;// for storing outgoing serial data
int pir_sensor = 2; // pir sensor is connected to digital pin 2 of the Arduino Uno board
int relay_pin = 3; // relay with Alarm or/and light connected to digital pin 3 of the Arduino Uno board
int switch_pin = 4; //magnetic contact switch connected to digital pin 4 of the Arduino Uno board
int pirStatus=0,switchStatus=0;//variables for pir and magnetic contact switch status

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);// baudrate for serial monitor
  SIM900.begin(19200); // baudrate for GSM shield
  Serial.println(" Logging time completed!");
  pinMode(pir_sensor, INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(switch_pin, INPUT);
  digitalWrite(relay_pin, LOW);
  delay(5000); // wait for 5 seconds
}

void loop() {
  pirStatus=digitalRead(pir_sensor);
  switchStatus=digitalRead(switch_pin);

  if(pirStatus ==HIGH || switchStatus==LOW){ 
    // the initial setup is if one of sensors detects intruder, but you can change
    // it if both sensors detects intruder - change || to &&
  
    outgoingData =  "Intruder detected\n";
    digitalWrite(relay_pin, HIGH;
    sendSMS(outgoingData);
    Serial.println(outgoingData);
    Serial.println("Message sent");
    delay(8000);
  }
  else
   {
   digitalWrite(relay_pin, LOW);
   delay(1000);
  }
*/
}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
  SIM900.println("AT + CMGS = \"+37168247489\"");  // recipient's mobile number, in international format

  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000);
  SIM900.println();
  delay(100);                                     // give module time to send SMS

}
