#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) // mirar si la com BT esta activada
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

BluetoothSerial SerialBT; // com bluetooth

const int heartRates[] = {72, 72, 71, 73};
const float temps[] = {36.5, 36.7, 36.6, 36.5};
const int SPO2s[] = {99, 97, 98, 99};

const int arraySize = sizeof(heartRates) / sizeof(heartRates[0]); // llargada array

const int ledPin = 12; 


void setup() {

  Serial.begin(9600);
  SerialBT.begin("ESP32_G6_P2");

  pinMode(ledPin, OUTPUT);

  randomSeed(analogRead(A0)); // generar random seed
}

void loop() {

  int randomIndex = random(arraySize);

  int hearRate = heartRates[randomIndex];
  float temp = temps[randomIndex];
  int SPO2 = SPO2s[randomIndex];

  Serial.println(String(hearRate) + "," + String(temp) + "," + String(SPO2));
  SerialBT.println(String(hearRate) + "," + String(temp) + "," + String(SPO2));
  
  digitalWrite(ledPin, HIGH);

  delay(1000);
}
