// ---------------------------------------------------------------------------
// Automated Sensor Light Switch - Edwork (ed.boal@edwork.org) 2017-2017
// GitHub: https://github.com/edwork/AutoSwitch
// ---------------------------------------------------------------------------
// -System powers on, LED blinks for 5 seconds allowing you to get out of the way
// -System enters loop
//   -System waits for button press OR ultrasonic sense
//     -IF ON button or Ultrasonic THEN send power on signal & return
//     -IF OFF button THEN send power off signal, wait 10 seconds, & return
//
// TODO:
// -Add logic + design for light sensor, disable ultrasonic sensor during daylight

#include <NewPing.h>
#include <RCSwitch.h>
#define TRIGGER_PIN  11     // Pin tied to Ultrasonic Trigger
#define ECHO_PIN     12     // Pin tied to Ultrasonic Echo
#define MAX_DISTANCE 10     // Max distance to ping from
#define PULSE_LENGTH 189    // Pulse length for signal being sent
#define TX_PIN 10           // Pin tied to Transmitter Data Pin
#define BIT_LENGTH 24       // Bit length
#define SIGNAL_CODE 1120003 // Code that turns on X device you are working with

RCSwitch mySwitch = RCSwitch();                     // Setting up Transmitter
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Ultrasonic Sensor Setup

void setup() {
  Serial.begin(115200);                  // Serial Output Setup - for Debug
  pinMode(LED_BUILTIN, OUTPUT);          // LED Setup - for monitoring the device's activity
  mySwitch.enableTransmit(TX_PIN); 
  mySwitch.setPulseLength(PULSE_LENGTH);
}

void loop() {
  delay(50);                     // Wait 50ms between pings
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
    if (sonar.ping_cm() > 0){
    mySwitch.send(SIGNAL_CODE, BIT_LENGTH);
    delay(100);
  }
}
