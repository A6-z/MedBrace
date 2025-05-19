#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   


//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int ledPin = 11;  
const int buzzerPin = 8;        // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;     
      // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(115200);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(ledPin, OUTPUT);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);
    
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
    int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                  // "myBPM" hold this BPM value now. 
    Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: ");                        // Print phrase "BPM: " 
    Serial.println(myBPM);

    if(myBPM > 100){
      tone(buzzerPin, 1000); 
      digitalWrite(ledPin, HIGH);
    }
    else{
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
    }
  }
    delay(20);                    // considered best practice in a simple sketch.

  }

  
