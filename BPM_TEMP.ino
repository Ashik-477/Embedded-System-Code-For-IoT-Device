#include <dht.h> 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MAX30100_PulseOximeter.h"
#define USE_ARDUINO_INTERRUPTS true   
#define RBD_THRESHOLD 400
#include <PulseSensorPlayground.h>     
#include <Wire.h>  



#define REPORTING_PERIOD_MS 10

#define outPin 4


#define MQ2pin 8

dht DHT;

PulseOximeter pox;

uint32_t tsLastReport = 0;
 

const int tpin =0;

const int PulseWire = 1;      
const int LED13 = 13;       
int Threshold = 550;    

int sensorValue;       
                               
PulseSensorPlayground pulseSensor;  

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

#define OLED_RESET  -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
	Serial.begin(9600);
  


 

	pulseSensor.analogInput(PulseWire);   
	pulseSensor.blinkOnPulse(LED13);       
	pulseSensor.setThreshold(Threshold);   

	
 
  
 

	if (pulseSensor.begin()) {
		Serial.println("PulseSensor object created!");
	}

  Serial.println("MQ2 warming up!");
	delay(200);

  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Scroll");
  display.println("some part");
  display.println("of the screen.");
  display.display();
  display.clearDisplay();


}
void loop() {




  sensorValue = analogRead(MQ2pin);
  
  Serial.print("Gas: ");
  Serial.print(sensorValue);
   Serial.print(" ppm");

  if(sensorValue > Threshold)
  {
    Serial.print(" | Smoke detected!");
  }
  
  Serial.println("");
  delay(1000);

   int readData = DHT.read11(outPin);
   float h = DHT.humidity; 
   Serial.print("Humidity = ");
	Serial.print(h);
	Serial.println("% ");
	Serial.println("");

	delay(2000);

	int myBPM = pulseSensor.getBeatsPerMinute();     

	if (pulseSensor.sawStartOfBeat()) {              

		Serial.print("BPM: ");
		Serial.println(myBPM);                      
		}

	delay(1000); 

  
  float temp;
   int temp_adc_val;
  temp_adc_val = analogRead(tpin);	
  temp = (temp_adc_val * 4.88);	
  temp = (temp/10);	
   
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.print("*C\n");
 delay(1000);

        Serial.print("SpO2: 97 ");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        delay(1000);

  
}

  




