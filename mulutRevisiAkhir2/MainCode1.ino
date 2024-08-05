#include <Servo.h>

const int soundSensorPin = A0; // Hubungkan sensor suara ke pin analog A0
const int servoPin = 9;        // Hubungkan servo ke pin digital 9
const int redLedPin = 8;       // Hubungkan led merah ke pin digital 3

Servo myServo; // Membuat objek servo

// int storedAngles[] = {30, 55, 180}; // Array untuk menyimpan derajat servo yang telah ditentukan
int storedAngles[] = {30, 180}; // Array untuk menyimpan derajat servo yang telah ditentukan
int mouthMoveCount = 0; // Variabel untuk melacak jumlah gerakan mulut

void setup() {
  pinMode(soundSensorPin, INPUT); // Set pin sensor suara sebagai input
  pinMode(redLedPin, OUTPUT);     // Set pin lampu LED sebagai output, supaya lampu dapat menyala
  myServo.attach(servoPin);       // Menghubungkan servo ke pin digital 9
  Serial.begin(9600);             // Mulai komunikasi serial dengan kecepatan 9600 bps

  digitalWrite(redLedPin, HIGH); // Hidupkan lampu LED merah
  delay(3000); // jeda 3 detik, sebelum mulut mulai bergerak
  digitalWrite(redLedPin, LOW); // Matikan lampu LED merah
}

void loop() {
  

  int soundLevel = analogRead(soundSensorPin);
  Serial.println(soundLevel);

  if (soundLevel) {
    int randomIndex = random(0, 2); // Jika sensor suara menerima suara dengan ambang frekuensi lebih dari 100
    myServo.write(storedAngles[randomIndex]); // Maka derajat servo (storedAngles) akan dieksekusi secara acak
    delay(100);
    // mouthMoveCount++; // Tambahkan 1 ke jumlah gerakan mulut

    // // Jika jumlah gerakan mulut mencapai 100 - 130x , hidupkan lampu LED merah
    // if (mouthMoveCount >= 100 && mouthMoveCount <= 130) {
    //   digitalWrite(redLedPin, HIGH); // Hidupkan lampu LED merah
    // }

    // // Jika jumlah gerakan mulut melebihi/sama dengan 130x, matikan lampu LED merah
    // if (mouthMoveCount >= 130) {
    //   digitalWrite(redLedPin, LOW); // Matikan lampu LED merah
    //   mouthMoveCount = 0; // Reset jumlah gerakan mulut
    // }

  } 
  // else {
  //   digitalWrite(redLedPin, LOW); // Matikan lampu LED merah jika tidak ada suara
  // }
}
