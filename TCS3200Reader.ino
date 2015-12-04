// Code for running color sensor
// Remember: Frequency-In ("OUT") must be on Digital Pin 5 (or whatever is mapped to the 16 Bit Hardware Counter1)

#include <FreqCounter.h> 				// Start frequency counting library

int S0_pin = 8;							// Initiate settings pins, variables, etc.
int S1_pin = 9;
int S2_pin = 10;
int S3_pin = 11;

int LED_pin = A0;

long int red;
long int green;
long int blue;
long int white;

void setup() {
  Serial.begin(9600);                   // Connect to the serial port
  Serial.println("Color Sensor");		// If nothing else works, at least this should
  digitalWrite(S0, HIGH);				// Set attenuation (Default is HIGH LOW, which is attenuation to 20%)
  digitalWrite(S1, LOW);
}

void loop() {

	FreqCounter::f_comp= 8;             // Set compensation to 12
	
	digitalWrite(S2, HIGH);				// Set config pins
	digitalWrite(S3, LOW);
	FreqCounter::start(100);            // Start counting with gatetime of 100ms
	while (FreqCounter::f_ready == 0)   // Wait until counter ready
	white=FreqCounter::f_freq;			// Read result
	
	digitalWrite(S2, LOW);
	digitalWrite(S3, LOW);
	FreqCounter::start(100);            
	while (FreqCounter::f_ready == 0)   
	red=FreqCounter::f_freq;            
 
	digitalWrite(S2, HIGH);
	digitalWrite(S3, HIGH);
	FreqCounter::start(100);            
	while (FreqCounter::f_ready == 0)   
	green=FreqCounter::f_freq;
 
	digitalWrite(S2, LOW);
	digitalWrite(S3, HIGH);
	FreqCounter::start(100);            
	while (FreqCounter::f_ready == 0)   
	blue=FreqCounter::f_freq;
 
	LED = analogRead(LED_pin);			// Read ghetto photodiode voltage
	
	Serial.print(millis());				// ALL of the Serial.print
	Serial.print(",");
	Serial.print(LED);
	Serial.print(",");
	Serial.print(white);
	Serial.print(",");
	Serial.print(red);
	Serial.print(",");
	Serial.print(green);
	Serial.print(",");
	Serial.println(blue);
}
