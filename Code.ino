/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(10,11);// RX, TX 

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "aOgRRumsHwyF1etXbW_TAK2gtxCQPN9z";

// Define to which pin of the Arduino the output of the LM35 is connected:
#define sensorPin A0
// Define analog input voltage
#define ANALOG_IN_PIN A1

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
float WS=0.0;   
int reading = 0;
float voltage = 0;
float temperature = 0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;
 
WidgetTerminal terminal (V5);
BLYNK_READ(V5)
 {
  Blynk.virtualWrite(V5,temperature);
 }
BLYNK_READ(V4)
{
  Blynk.virtualWrite(V4,WS);
}
void setup()
{
  DebugSerial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial.println("DC Voltage Test");

  Blynk.begin(Serial, auth);
}

void loop() {
  Blynk.run();
  // Get a reading from the temperature sensor:
  reading = analogRead(sensorPin);

  // Convert the reading into voltage:
  voltage = reading * (5000 / 1024.0);

  // Convert the voltage into the temperature in degree Celsius:
  temperature = voltage / 10;

  // Print the temperature in the Serial Monitor:
  Serial.print("Temprature = ");
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");

  delay(1000); // wait a second between readings
  // Read the Analog Input
   adc_value = analogRead(ANALOG_IN_PIN);
   
   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
   // Calculate voltage at divider input
   in_voltage = adc_voltage / (R2/(R1+R2)) ; 
   
// wind speed
    WS=(((in_voltage-0.4)/1.6)*32.4)*2.237;    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
   // Print results to Serial Monitor to 2 decimal places
  Serial.print("Wind Spead = ");
  Serial.println(WS, 2);
   
  // Short delay
  delay(500);
}
