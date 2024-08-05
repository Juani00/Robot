#include <Servo.h>

const int soundSensorPin = A0; // Hubungkan sensor suara ke pin analog A0
const int servoPin = 9;        // Hubungkan servo ke pin digital 9
const int redLedPin = 8;       // hubungkan led merah ke pin digital 3

const int switchPin = 7;       // pin 7 sebagai saklar yang terhubung ke kunci kontak(seperti pada arduino nano, yang mengontrol pergerakan mata)



Servo myServo; // Membuat objek servo

int storedAngles[] = {30, 55, 180}; // Array untuk menyimpan derajat servo yang telah ditentukan

void setup() {
  pinMode(switchPin, INPUT); // set pin saklar sebagai INPUT / penerima data
  
  pinMode(soundSensorPin, INPUT); // Set pin sensor suara sebagai input
  pinMode(redLedPin, OUTPUT);     // set pin lampu LED sebagai output, supaya lampu dapat hidup
  myServo.attach(servoPin);       // Menghubungkan servo ke pin digital 9
  Serial.begin(9600);             // Mulai komunikasi serial dengan kecepatan 9600 bps
}

void loop() {
 
  int swtichStatus = digitalRead(switchPin);
  Serial.print("Swithc status: ");
  Serial.println(swtichStatus); // sebagai debugging proses

  int soundLevel = analogRead(soundSensorPin);
  Serial.println(soundLevel);

  // Jika saklar dimatikan, hentikan semua proses dan pergerakan mulut yang terjadi
  if (swtichStatus == LOW) {

      /* ketika saklar dimatikan,
         nyalakan lampu led merah sebentar sebelum seluruh proses berhenti
         lalu ketika proses berhenti, lampu led padam. */

      digitalWrite(redLedPin, HIGH); // menyalakan lampu led merah
      delay(500); // tunggu 0.5 detik
      myServo.write(180); // merubah posisi derajat servo ke 180 (menutup mulut robot)
      delay(200); // tunggu 0.2 detik
      digitalWrite(redLedPin, LOW); // mematikan lampu led yang menyala
      
  }

  // Jika saklar dihidupkan, mulai semua proses dan pergerakan mulut 
  if (swtichStatus == HIGH) {
    Serial.println("Mulai menggerakan Mulut Robot..");

    if (soundLevel > 100) {
      int randomIndex = random(0, 3);            // jika sensor suara menerima suara dengan ambang frekuensi lebih dari 100
      myServo.write(storedAngles[randomIndex]);  // maka derajat servo(storedAngles) akan di eksekusi secara acak
      delay(500);

        if (soundLevel > 400) {
          Serial.println("\tLampu merah AKTIF..");
          digitalWrite(redLedPin, HIGH); // jika sensor suara mendapatkan frekuensi/suara lebih besar dari 600/keras
                                        // lampu led merah diaktifkan.
          delay(900);                              
          digitalWrite(redLedPin, LOW); // jika tidak, lampu led merah akan di non-aktifkan.
          Serial.println("__Lampu merah di Non-Aktifkan__");
        } 
    }  
  }


}
