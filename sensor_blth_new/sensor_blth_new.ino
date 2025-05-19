int buzzerPin = 16;

const int ledPin1 = 4;
const int ledPin2 = 5;

#include "DFRobot_BloodOxygen_S.h"
#include <Wire.h>
#include "BluetoothSerial.h"

#define I2C_COMMUNICATION  // Use I2C for communication

#ifdef  I2C_COMMUNICATION
  #define I2C_ADDRESS    0x57  // Default I2C address for the sensor
  DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);  // Initialize sensor with I2C communication
#else
  // Code for serial communication (not needed for your case)
#endif

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) // mirar si la com BT esta activada
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

BluetoothSerial SerialBT; // aixo es la com bluetooth

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
  SerialBT.begin("ESP32_G6_P1");
  Wire.begin(21, 22); // Pins 21 and 22 are set as SDA and SCL pins
  // Wait for sensor initialization
  while (false == MAX30102.begin()) {
    Serial.println("Init failed!");
    delay(1000);
  }
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  Serial.println("Init success!");
  Serial.println("Start measuring...");
  MAX30102.sensorStartCollect();  // Start collecting data from the sensor
}

void loop() {
  // Get heartbeat and SPO2 data from the sensor
  MAX30102.getHeartbeatSPO2();

  float rawTemp = MAX30102.getTemperature_C();
  float correctedTemp = rawTemp + 0.5;

  Serial.println(String(MAX30102._sHeartbeatSPO2.Heartbeat) + "," + String(correctedTemp) + "," + String(MAX30102._sHeartbeatSPO2.SPO2));
  SerialBT.println(String(MAX30102._sHeartbeatSPO2.Heartbeat) + "," + String(correctedTemp) + "," + String(MAX30102._sHeartbeatSPO2.SPO2));
  
  digitalWrite(ledPin2, HIGH);

  if(50 > MAX30102._sHeartbeatSPO2.Heartbeat || MAX30102._sHeartbeatSPO2.Heartbeat > 150){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    tone(buzzerPin, 1000);

  }

 if(correctedTemp > 42 || correctedTemp < 30){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    tone(buzzerPin, 1000);

 }

  delay(1000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  noTone(buzzerPin);
}