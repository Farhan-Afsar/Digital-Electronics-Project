#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(9, 10); // RX, TX pins for GSM module


const int ledPin = 2; // LED pin
const int buzzerPin = 3; // Buzzer pin
const int gasSensorPin = A0; // Gas sensor analog pin
const int fan = 4;   //fan

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(gasSensorPin, INPUT);
  Serial.begin(9600); // initialize serial monitor
  mySerial.begin(9600); // initialize GSM module
  delay(1000);
  
}

void loop() {
  int gasValue = digitalRead(gasSensorPin); // read gas sensor value
  delay(500); // wait for a moment

  if (gasValue == HIGH) { // if gas level is high
    digitalWrite(ledPin, HIGH); // turn on LED light
    digitalWrite(buzzerPin, HIGH); // turn on buzzer sound
    digitalWrite(fan, HIGH);    //turn on fan
    delay(5000); // wait for 5 seconds
    sendMessage("Gas Detected!"); // send message
    digitalWrite(ledPin, LOW); // turn off LED light
    digitalWrite(buzzerPin, LOW); // turn off buzzer sound
    digitalWrite(fan, LOW);   // turn off fan
  }
}

void sendMessage(String message) {
  mySerial.println("AT+CMGF=1"); // set message format to text mode
  delay(1000);
  mySerial.print("AT+CMGS=\"+8801705299933\"\r"); // specify phone number
  delay(1000);

  mySerial.print(message); // send message
  delay(100);
  mySerial.write(26);
  delay(1000);
  Serial.println("Message sent.");
  delay(10000);
}