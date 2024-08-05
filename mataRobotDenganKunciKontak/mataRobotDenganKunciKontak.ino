#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#define SERVO_FREQ 60 // Frekuensi PWM, sesuaikan dengan spesifikasi servo Anda
#define SERVO_KANAN_PIN 1 // Pin servo untuk mata kanan (pada pca8695)
#define SERVO_KIRI_PIN 2 // Pin servo untuk mata kiri (pada pca8695)
#define SERVO_KELAPAK_PIN 0 // Pin servo untuk kelopak mata (pada pca8695)
#define SERVOMIN 150   // Lebar pulsa minimum untuk servo
#define SERVOMAX 600   // Lebar pulsa maksimum untuk servo
#define DELAY_BETWEEN_STEPS 10 // Waktu delay antara setiap langkah (ms)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Inisialisasi objek PCA9685

const int switchPin = 2; // pin 2 (Digital Pin) pada Arduino Board, yang digunakan untuk membaca status saklar.
bool robotOn = false; // variabel untuk menandai status robot (hidup/mati)

void setup() {
  pinMode(switchPin, INPUT); // Set pin saklar sebagai input

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set frekuensi PWM


  moveEyelidServo(10);
  delay(1000);
  moveEyelidServo(150);




  Serial.begin(9600);
}

void loop() {
  int switchStatus = digitalRead(switchPin); // baca status saklar

  // Jika saklar dimatikan, hentikan semua proses dan pergerakan mata
  if (switchStatus == LOW) {
    if (robotOn) {
      Serial.println("Mematikan seluruh proses Robot, yang sedang berjalan.");
      // stopEyes(); // memanggil fungsi stopEyes(), untuk menghentikan gerakan mata robot
      robotOn = false; // Atur status robot menjadi mati
    }
    delay(100); // Tunggu sebentar untuk stabil
    return; // Keluar dari loop
  }

  // Jika saklar dinyalakan dan robot masih dalam status mati
  if (switchStatus == HIGH && !robotOn) {
    Serial.println("Menyalakan Robot....");
    robotOn = true; // Atur status robot menjadi hidup
    controlEyes(); // memanggil fungsi controlEyes(), untuk menggerakan mata robot
  }

  delay(100);
}
void moveAndWait(uint16_t delayTime) {
  delay(delayTime);
  if (digitalRead(switchPin) == LOW) return; // Periksa saklar, jika mati keluar dari loop
}

// Definisikan jumlah langkah gerakan mata
const int NUM_EYE_MOVEMENTS = 10;

// Deklarasikan array yang berisi pointer ke fungsi gerakan mata
void (*eyeMovements[NUM_EYE_MOVEMENTS])() = {
  moveEyetoCenter,
  moveEyetoLeftNormalSpeed,
  moveEyeToCenterSlowySpeed,
  moveEyetoLeftSlowySpeed,
  moveEyetoRightNormalSpeed,
  moveEyetoCenter,
  moveEyetoRightSlowySpeed,
  moveEyetoLeftSlowySpeed,
  moveEyeToCenterSlowySpeed,
  moveEyetoRightSlowySpeed
};

// Fungsi untuk mengacak urutan gerakan mata
void shuffleEyeMovements() {
  for (int i = NUM_EYE_MOVEMENTS - 1; i > 0; i--) {
    int j = random(0, i + 1);
    // Tukar posisi elemen array
    void (*temp)() = eyeMovements[i];
    eyeMovements[i] = eyeMovements[j];
    eyeMovements[j] = temp;
  }
}

void controlEyes() {
  // Acak urutan gerakan mata setiap kali fungsi dipanggil
  shuffleEyeMovements();

  // Lakukan setiap gerakan mata secara berurutan
  for (int i = 0; i < NUM_EYE_MOVEMENTS; i++) {
    // Jika saklar dimatikan, hentikan proses
    if (digitalRead(switchPin) == LOW) {
      // Posisikan mata ke tengah
      moveEyetoCenter();
      // Menutup kelopak mata
      moveEyelidServo(10);
      // Tunggu saklar diaktifkan kembali
      while (digitalRead(switchPin) == LOW) {
        delay(100);
      }
      // Jika saklar diaktifkan kembali, kelopak mata yang tertutup tadi dibuka
      moveEyelidServo(150);
      return;
    }
    
    // Panggil fungsi gerakan mata
    eyeMovements[i]();
    moveAndWait(1500); // Tunggu setelah setiap gerakan mata
  }
}


/*_____________________________________________________________________________ */

/*

moveEyeToCenter()   = mengarahkan kedua mata menuju tengah
moveEyeToCenterSlowySpeed() = mengarahkan kedua mata menuju tengah secara perlahan

moveEyeToLeftNormalSpeed() = mengarahkan kedua mata menuju kiri
moveEyeToRightNormalSpeed() = mengarahkan kedua mata menuju kiri secara perlahan

moveEyeToLeftSlowySpeed() = mengarahkan kedua mata menuju kanan
moveEyeToRightSlowySpeed() = mengarahkan kedua mata menuju kanan secara perlahan


*/


// Fungsi untuk menggerakkan servo mata ke posisi tertentu
void moveEyeServos(uint16_t angle) {
  pwm.setPWM(SERVO_KANAN_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(SERVO_KIRI_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

// Fungsi untuk menggerakkan servo kelopak mata ke posisi tertentu
void moveEyelidServo(uint16_t angle) {
  pwm.setPWM(SERVO_KELAPAK_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

/*_____________________________________________________________________________ */

// fungsi untuk menggerakan mata ke kiri dengan kecepatan 10ms/normal
void moveEyetoLeftNormalSpeed() {
  for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS);
  }
 
}

// fungsi untuk menggerakan mata ke kanan dengan kecepatan 10ms/normal
void moveEyetoRightNormalSpeed() {
  for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS);
  }
}

// fungsi untuk menggerakan mata ke kiri dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoLeftSlowySpeed() {
  for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS + 30);
  }
}


//fungsi untuk menggerakan mata ke kanan dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoRightSlowySpeed() {
  for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS + 30);
  }
}

// fungsi untuk menggerakan mata ke tengah
void moveEyetoCenter() {
  for (int i = 0; i <= 25; i++) {
    moveEyeServos(i);                           
    delay(DELAY_BETWEEN_STEPS);                
  }
  // delay(1000); // Tunggu sebentar di posisi tengah
}

void moveEyeToCenterSlowySpeed() {
  for (int i = 0; i <= 25; i++) {
    moveEyeServos(i);
    delay(DELAY_BETWEEN_STEPS + 30);
  }
}

// fungsi mengontrol kelopak mata untuk membuka dan tutup.
void openAndCloseEyelid() {
  moveEyelidServo(10); // menutup kelopak mata
  delay(500);
  moveEyelidServo(150); // membuka kelopak mata
  delay(500);
}


void closeEyeLid() {
  moveEyeServos(25); // mengarahkan posisi mata ke arah tengah /  posisi mata menatap ke depan
  delay(2500); // memberi jarak waktu 2 detik, ketika mata telah ditengah, kemudian kelopak mata akan tertutup
  moveEyelidServo(10); // menutup kelopak mata

}


