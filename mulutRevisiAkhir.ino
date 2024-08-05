#include <Servo.h>

const int soundSensorPin = A0; // Hubungkan sensor suara ke pin analog A0
const int servoPin = 9;        // Hubungkan servo ke pin digital 9
const int redLedPin = 8;       // hubungkan led merah ke pin digital 3


Servo myServo; // Membuat objek servo

int storedAngles[] = {30, 55, 180}; // Array untuk menyimpan derajat servo yang telah ditentukan

void setup() {
  pinMode(soundSensorPin, INPUT); // Set pin sensor suara sebagai input
  pinMode(redLedPin, OUTPUT);     // set pin lampu LED sebagai output, supaya lampu dapat hidup
  myServo.attach(servoPin);       // Menghubungkan servo ke pin digital 9
  Serial.begin(9600);             // Mulai komunikasi serial dengan kecepatan 9600 bps
}

void loop() {
 
  int soundLevel = analogRead(soundSensorPin);
  Serial.println(soundLevel);

  if (soundLevel > 100) {
    int randomIndex = random(0, 3);            // jika sensor suara menerima suara dengan ambang frekuensi lebih dari 100
    myServo.write(storedAngles[randomIndex]);  // maka derajat servo(storedAngles) akan di eksekusi secara acak
    delay(200);


             
  }  

  
}
